#include "noSuchVisitorException.h++"

namespace Praetorian {
    namespace Basics {
        namespace Visitor {

            NoSuchVisitorException::NoSuchVisitorException()
            : LogicError("No such visitor.",1)
            {
            }

        }
    }
}
