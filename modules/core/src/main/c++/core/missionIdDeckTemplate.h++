#ifndef TYRANT_CACHE_CORE_MISSIONIDTEMPLATE_HPP
    #define TYRANT_CACHE_CORE_MISSIONIDTEMPLATE_HPP

    #include <memory>
    #include <list>
    #include "deckTemplate.h++"

    namespace TyrantCache {
        namespace Core {

            class MissionIdDeckTemplate : public DeckTemplate {
                public:
                    typedef std::shared_ptr<MissionIdDeckTemplate> Ptr;
                    CREATE_VISITOR_INTERFACE(MissionIdDeckTemplate);
                private:
                    unsigned int missionId;
                public:
                    MissionIdDeckTemplate(unsigned int missionId);
                    virtual operator std::string() const;

                    virtual void accept(::TyrantCache::Visitor::AcyclicVisitor & visitor);
            };
        }
    }

#endif

