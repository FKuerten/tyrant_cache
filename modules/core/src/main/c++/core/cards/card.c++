#include "card.h++"

namespace Tyrant {
    namespace Core {
        namespace Cards {

            bool operator< (Card const & a, Card const & b)
            {
                if (a.name < b.name) {
                    return true;
                } else if (a.name > b.name) {
                    return false;
                }
                return false;
            }

        }
    }
}
