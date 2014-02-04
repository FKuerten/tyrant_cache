#ifndef TYRANT_CACHE_CORE_QUESTDECK_HPP
    #define TYRANT_CACHE_CORE_QUESTDECK_HPP

#include <memory>
#include "deckTemplate.h++"

namespace TyrantCache {
    namespace Core {

        class QuestDeckTemplate : public DeckTemplate {
        public:
            typedef std::shared_ptr<QuestDeckTemplate> Ptr;

        private:
            unsigned int questId;

        public:
            QuestDeckTemplate(unsigned int questId);
            operator std::string() const;
        };
    }
}


#endif
