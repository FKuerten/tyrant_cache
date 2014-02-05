#include "autoDeckTemplate.h++"
#include <errorHandling/assert.h++>
#include <errorHandling/exceptions.h++>

namespace TyrantCache {
    namespace Core {

        AutoDeckTemplate::AutoDeckTemplate(std::list<unsigned int> const & ids)
        : DeckTemplate()
        {
            std::list<unsigned int>::const_iterator iter = ids.begin();
            unsigned int const commanderId = *iter;
            this->commander = commanderId;
            for(iter++ ;iter != ids.end(); iter++) {
                unsigned int cardId = *iter;
                this->cards.insert(cardId);
            }
        }

        
        AutoDeckTemplate::operator std::string() const
        {
            std::stringstream ssString;
            ssString << "IDS:";
            ssString << this->commander;
            for(std::multiset<unsigned int>::const_iterator iter = this->cards.begin()
               ;iter != this->cards.end()
               ;iter++
               )
            {
                ssString << ",";
                ssString << *iter;
            }
            return ssString.str();
        }

        CREATE_VISITOR_METHOD(AutoDeckTemplate)
    }
}
