#ifndef TYRANT_CACHE_CORE_DECKTEMPLATE_HPP
    #define TYRANT_CACHE_CORE_DECKTEMPLATE_HPP

    #include <string>
    #include <memory>

    namespace TyrantCache {
        namespace Core {

            class DeckTemplate {
                public:
                    typedef std::shared_ptr<DeckTemplate> Ptr;
                    typedef std::shared_ptr<DeckTemplate const> ConstPtr;                    

                protected:
                    DeckTemplate();

                public:
                    virtual ~DeckTemplate();
                    virtual operator std::string() const = 0;
            };

        }
    }
    
#endif
