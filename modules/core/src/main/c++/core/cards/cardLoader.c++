#include "cardLoader.h++"
#include <errorHandling/exceptions.h++>
#include <pugixml.hpp>
#include <iostream>
#include <boost/lexical_cast.hpp>

namespace Tyrant {
    namespace Core {
        namespace Cards {

            CardRarity parseRarity(std::string strRarity, std::string strUnique)
            {
                unsigned int intRarity = boost::lexical_cast<unsigned int>(strRarity);
                switch(intRarity) {
                    case 1:
                        return CardRarity::COMMON;
                    case 2:
                        return CardRarity::UNCOMMON;
                    case 3:
                        if(strUnique.empty()) {
                            return CardRarity::RARE;
                        } else {
                            return CardRarity::UNIQUE;
                        }
                    case 4:
                        return CardRarity::LEGENDARY;
                    default:
                        throw InvalidUserInputError("Unknown card rarity.");
                }
            }

            CardType parseType(unsigned int id)
            {
                id %= 4000;
                if (id < 1000) {
                    return CardType::ASSAULT;
                } else if (id < 2000) {
                    return CardType::COMMANDER;
                } else if (id < 3000) {
                    return CardType::STRUCTURE;
                } else {
                    return CardType::ACTION;
                }
            }

            Cards loadFromXMLFile(std::string const & fileName)
            {
                Cards cards;
                pugi::xml_document document;
                document.load_file(fileName.c_str());
                pugi::xml_node root = document.first_child();

                //std::clog << root.name() << std::endl;

                for(pugi::xml_node cardNode = root.first_child()
                   ;cardNode
                   ;cardNode = cardNode.next_sibling()
                   )
                {
                    Card card;
                    if (cardNode.name() == std::string("unit")) {
                        card.id = boost::lexical_cast<unsigned int>(cardNode.child_value("id"));
                        card.name = cardNode.child_value("name");
                        card.rarity = parseRarity(cardNode.child_value("rarity")
                                                 ,cardNode.child_value("unique")
                                                 );
                        card.type = parseType(card.id);

                        //std::clog << "id=" << card.id << " "
                        //          << "name=" << card.name << " "
                        //          << "rarity=" << static_cast<unsigned int>(card.rarity) << " "
                        //          << "type=" << static_cast<unsigned int>(card.type) << " "
                        //          ;//<< std::endl;
                        cards[card.id] = card;
                        //std::clog << static_cast<unsigned int>(cards[card.id].type) << std::endl;
                    }
                }
                return cards;
            }

        }
    }
}
