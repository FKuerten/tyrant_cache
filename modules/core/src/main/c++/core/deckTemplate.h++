#ifndef TYRANT_CACHE_CORE_DECKTEMPLATE_HPP
    #define TYRANT_CACHE_CORE_DECKTEMPLATE_HPP

    #include <string>
    #include <memory>
    #include <visitor/acyclicVisitor.h++>

    namespace Tyrant {
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

                    /**
                     * Visitor stuff.
                     * We use the acyclic visitor pattern.
                     */
                    virtual void accept(Praetorian::Basics::Visitor::AcyclicVisitor & visitor) = 0;
            };

        }
    }

#endif
