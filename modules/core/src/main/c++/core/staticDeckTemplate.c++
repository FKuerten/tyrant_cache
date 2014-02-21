#include "staticDeckTemplate.h++"

namespace Tyrant {
    namespace Core {

        StaticDeckTemplate::StaticDeckTemplate()
        {}

        StaticDeckTemplate::~StaticDeckTemplate() {}

        unsigned int
        StaticDeckTemplate::getCommanderId() const
        {
            return this->commanderId;
        }


    }
}

