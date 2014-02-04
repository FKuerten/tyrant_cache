#ifndef TYRANT_CACHE_CORE_SIMULATIONTASK_HPP
    #define TYRANT_CACHE_CORE_SIMULATIONTASK_HPP

    #include "deckTemplate.h++"
        
    namespace TyrantCache {
        namespace Core {

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
                    unsigned int randomSeed;
                    unsigned int numberOfRounds;
                    bool useRaidRules;

                    DeckDescription attacker;
                    DeckDescription defender;

                public:
                    SimulationTask();
            };
        }
    }
#endif
    
