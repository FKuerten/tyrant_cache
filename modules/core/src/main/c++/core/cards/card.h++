#ifndef TYRANT_CACHE_CORE_CARDS_CARD_HPP
    #define TYRANT_CACHE_CORE_CARDS_CARD_HPP

    #include <string>

    namespace Tyrant {
        namespace Core {
            namespace Cards {

                enum class CardType {
                    COMMANDER,
                    ASSAULT,
                    STRUCTURE,
                    ACTION
                };

                enum class CardRarity {
                    COMMON,
                    UNCOMMON,
                    RARE,
                    UNIQUE,
                    LEGENDARY
                };

                class Card {
                    public:
                        unsigned int id;
                        std::string name;
                        CardType type;
                        CardRarity rarity;

                    public:
                };

                bool operator< (Card const & a, Card const & b);

            }
        }
    }

#endif
