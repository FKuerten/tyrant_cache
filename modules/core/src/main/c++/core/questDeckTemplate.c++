#include "questDeckTemplate.h++"

#include <boost/lexical_cast.hpp>

namespace Tyrant {
    namespace Core {

        QuestDeckTemplate::QuestDeckTemplate(unsigned int questId)
        : questId(questId)
        {
        }

        QuestDeckTemplate::operator std::string() const
        {
            return "QUESTID:" + boost::lexical_cast<std::string>(this->questId);
        }

        CREATE_VISITOR_METHOD(QuestDeckTemplate)

    }
}
