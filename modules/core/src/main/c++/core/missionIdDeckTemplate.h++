#ifndef TYRANT_CORE_MISSIONIDDECKTEMPLATE_HPP
    #define TYRANT_CORE_MISSIONIDDECKTEMPLATE_HPP

    #include <memory>
    #include <list>
    #include "deckTemplate.h++"

    namespace Tyrant {
        namespace Core {

            class MissionIdDeckTemplate : public DeckTemplate {
                public:
                    typedef std::shared_ptr<MissionIdDeckTemplate> Ptr;
                    CREATE_VISITOR_INTERFACE(MissionIdDeckTemplate);
                public:
                    unsigned int missionId;
                public:
                    MissionIdDeckTemplate(unsigned int missionId);
                    virtual operator std::string() const;

                    virtual void accept(Praetorian::Basics::Visitor::AcyclicVisitor & visitor);
            };
        }
    }

#endif

