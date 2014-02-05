#include "multiDeckTemplate.h++"
#include <sstream>

namespace TyrantCache {
    namespace Core {

        MultiDeckTemplate::MultiDeckTemplate(
            std::multiset<DeckTemplate::Ptr> const & decks
            )
        : decks(decks)
        {
        }

        MultiDeckTemplate::operator std::string() const
        {
            std::stringstream ssString;
            for(DeckTemplate::Ptr const & deck: this->decks) {
                ssString << '{';
                ssString << static_cast<std::string>(*deck);
                ssString << '}';
                ssString << ';';
            }
            return ssString.str();
        }		

        std::multiset<DeckTemplate::Ptr> const &
        MultiDeckTemplate::getDecks() const
        {
            return this->decks;
        }

        CREATE_VISITOR_METHOD(MultiDeckTemplate)

    }
}
