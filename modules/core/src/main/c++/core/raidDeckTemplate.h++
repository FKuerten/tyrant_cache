#ifndef TYRANT_CACHE_CORE_RAIDDECK_HPP
    #define TYRANT_CACHE_CORE_RAIDDECK_HPP

#include <memory>
#include "deckTemplate.h++"

namespace TyrantCache {
    namespace Core {

        class RaidDeckTemplate : public DeckTemplate {
        public:
            typedef std::shared_ptr<RaidDeckTemplate> Ptr;
            CREATE_VISITOR_INTERFACE(RaidDeckTemplate);
        private:
            unsigned int raidId;

        public:
            RaidDeckTemplate(unsigned int raidId);
            operator std::string() const;

            virtual void accept(::TyrantCache::Visitor::AcyclicVisitor & visitor);
        };
    }
}


#endif
