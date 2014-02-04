#ifndef TYRANT_CACHE_CLI_SIMPLEORDEREDDECKTEMPLATE_HPP
    #define TYRANT_CACHE_CLI_SIMPLEORDEREDDECKTEMPLATE_HPP

    #include <memory>
    #include <list>
    #include <core/deckTemplate.h++>

    namespace C = TyrantCache::Core;
    namespace TyrantCache {
        namespace CLI {

            class SimpleOrderedDeckTemplate : public C::DeckTemplate {
                public:
                    typedef std::shared_ptr<SimpleOrderedDeckTemplate> Ptr;
                private:
                    unsigned int commander;
                    std::list<unsigned int> cards;
                public:
                    SimpleOrderedDeckTemplate(std::list<unsigned int> const & ids);
                    virtual operator std::string() const;
            };
        }
    }

#endif
