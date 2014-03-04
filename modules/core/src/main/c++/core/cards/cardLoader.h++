#ifndef TYRANT_CACHE_CORE_CARDS_CARDLOADER_HPP
    #define TYRANT_CACHE_CORE_CARDS_CARDLOADER_HPP

    #include <map>
    #include <set>
    #include "card.h++"

    namespace Tyrant {
        namespace Core {
            namespace Cards {

                typedef std::map<unsigned int, Card> Cards;
                typedef std::set<Card> CardSet;
                typedef std::multiset<Card> CardMSet;

                Cards loadFromXMLFile(std::string const & fileName);

            }
        }
    }

#endif

