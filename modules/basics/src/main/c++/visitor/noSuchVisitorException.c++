#include "noSuchVisitorException.h++"

namespace TyrantCache {
    namespace Visitor {

        NoSuchVisitorException::NoSuchVisitorException()
        : LogicError("No such visitor.",1)
        {
        }
    
    }
}
