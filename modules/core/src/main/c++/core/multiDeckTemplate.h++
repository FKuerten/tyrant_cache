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
                    CREATE_VISITOR_INTERFACE(MultiDeckTemplate);
                private:
                    std::multiset<DeckTemplate::Ptr> decks;
                public:
                    MultiDeckTemplate(std::multiset<DeckTemplate::Ptr> const & decks);
                    virtual operator std::string() const;

                    virtual void accept(::TyrantCache::Visitor::AcyclicVisitor & visitor);
                    
                    std::multiset<DeckTemplate::Ptr> const & getDecks() const;
                
            };

        }
    }
#endif

