#ifndef TYRANT_CACHE_CORE_MULTIDECKTEMPLATE_HPP
    #define TYRANT_CACHE_CORE_MULTIDECKTEMPLATE_HPP

    #include <memory>
    #include <set>
    #include "deckTemplate.h++"

    namespace TyrantCache {
        namespace Core {

            class MultiDeckTemplate : public DeckTemplate {
                public:
                    typedef std::shared_ptr<MultiDeckTemplate> Ptr;
                private:
                    std::multiset<DeckTemplate::Ptr> decks;
                public:
                    MultiDeckTemplate(std::multiset<DeckTemplate::Ptr> const & decks);
                    virtual operator std::string() const;

                    std::multiset<DeckTemplate::Ptr> const & getDecks() const;
                
            };

        }
    }
#endif

