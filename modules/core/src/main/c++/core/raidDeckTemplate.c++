#include "raidDeckTemplate.h++"

#include <boost/lexical_cast.hpp>

namespace TyrantCache {
    namespace Core {

        RaidDeckTemplate::RaidDeckTemplate(unsigned int raidId)
        : raidId(raidId)
        {
        }

        RaidDeckTemplate::operator std::string() const
        {
            return "RAIDID:" + boost::lexical_cast<std::string>(this->raidId);
        }
    }
}
