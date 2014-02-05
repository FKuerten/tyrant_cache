#include "missionIdDeckTemplate.h++"
#include <boost/lexical_cast.hpp>

namespace TyrantCache {
    namespace Core {

        MissionIdDeckTemplate::MissionIdDeckTemplate(unsigned int missionId)
        : missionId(missionId)
        {
        }

        MissionIdDeckTemplate::operator std::string() const
        {
            return "MISSIONID:" + boost::lexical_cast<std::string>(this->missionId);
        }

        CREATE_VISITOR_METHOD(MissionIdDeckTemplate)

    }
}
