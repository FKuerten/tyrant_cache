#include "simulationTask.h++"

namespace Tyrant {
    namespace Core {

        SimulationTask::SimulationTask()
        : minimalNumberOfGames(1000)
        , surge(false)
        , delayFirstAttacker(false)
        , battleGround(-1)
        , achievement(-1)
        , numberOfRounds(-1)
        , useRaidRules(tristate::UNDEFINED)
        {
        }
    }
}
