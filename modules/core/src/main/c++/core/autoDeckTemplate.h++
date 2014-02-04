#ifndef TYRANT_CACHE_CORE_AUTODECKTEMPLATE_HPP
    #define TYRANT_CACHE_CORE_AUTODECKTEMPLATE_HPP

    #include <memory>
    #include <set>
    #include <list>
    #include "deckTemplate.h++"

    namespace TyrantCache {
        namespace Core {

            class AutoDeckTemplate : public DeckTemplate {
                public:
                    typedef std::shared_ptr<AutoDeckTemplate> Ptr;
                private:
                    unsigned int commander;
                    std::multiset<unsigned int> cards;
                public:
                    AutoDeckTemplate(std::list<unsigned int> const & ids);
                    virtual operator std::string() const;
            };

        }
    }
#endif
