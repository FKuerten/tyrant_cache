#ifndef TYRANT_CACHE_CORE_SIMULATIONTASK_HPP
    #define TYRANT_CACHE_CORE_SIMULATIONTASK_HPP

    #include "deckTemplate.h++"
        
    namespace TyrantCache {
        namespace Core {

            enum class tristate {
                TRUE,
                FALSE,
                UNDEFINED
            };

            typedef DeckTemplate::Ptr DeckDescription;
            typedef signed int BattlegroundId;
            typedef signed int AchievementId;
                        
            struct SimulationTask {
                public:
                    unsigned long minimalNumberOfGames;
                    bool surge;
                    bool delayFirstAttacker;
                    BattlegroundId battleGround;
                    AchievementId achievement;
                    int numberOfRounds;
                    tristate useRaidRules;

                    DeckDescription attacker;
                    DeckDescription defender;

                public:
                    SimulationTask();
            };
        }
    }
#endif
    
