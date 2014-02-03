#include "simulationTask.h++"

namespace TyrantCache {
    namespace Core {

        SimulationTask::SimulationTask()
        : minimalNumberOfGames(1000)
        , surge(false)
        , delayFirstAttacker(false)
        , battleGround(-1)
        , achievementOptions(-1)
        , randomSeed(0)
        , numberOfRounds(50)
        , useRaidRules(false)
        {
        }
    }
}
