#ifndef TYRANT_CORE_STATICDECKTEMPLATE_HPP
    #define TYRANT_CORE_STATICDECKTEMPLATE_HPP

    #include <memory>
    #include <set>
    #include <list>
    #include "deckTemplate.h++"

    namespace Tyrant {
        namespace Core {

            class StaticDeckTemplate : public DeckTemplate {
                public:
                    typedef std::shared_ptr<StaticDeckTemplate> Ptr;
                    typedef std::shared_ptr<StaticDeckTemplate const> ConstPtr;

                public:
                    unsigned int commanderId;

                public:
                    StaticDeckTemplate();
                    ~StaticDeckTemplate();
                    virtual operator std::string() const = 0;

                    unsigned int getCommanderId() const;
                    virtual size_t getNumberOfNonCommanderCards() const = 0;
                    virtual unsigned int getCardIdAtIndex(size_t index) const = 0;
                    virtual StaticDeckTemplate::Ptr withCommander(unsigned int commanderId) const = 0;
                    virtual StaticDeckTemplate::Ptr withoutCardAtIndex(size_t index) const = 0;
                    virtual StaticDeckTemplate::Ptr withSwappedCards(size_t i, size_t j) const = 0;
                    virtual StaticDeckTemplate::Ptr withCard(unsigned int cardId) const = 0;
                    virtual StaticDeckTemplate::Ptr withCardAtIndex(unsigned int cardId , size_t index) const = 0;
                    virtual StaticDeckTemplate::Ptr withReplacedCardAtIndex(unsigned int cardId, size_t index) const = 0;
            };

        }
    }
#endif

