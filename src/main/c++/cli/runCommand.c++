#include "runCommand.h++"

#include "../configuration/configuration.h++"
#include "../cache/diskBackedCache.h++"
#include <iomanip>
/*
#include "../CORE/iterateDecksCore.hpp"
#include "../errorHandling/assert.h++"
#include <fstream>
#include "ownedCardsParser.hpp"
#include "../CACHE/multiDeckDecompositor.hpp"
*/

namespace C = TyrantCache::Core;
namespace Cache = TyrantCache::Cache;
namespace TyrantCache {
    namespace CLI {

        RunCommand::RunCommand(int verbosity
                              )
        {
            // the core
            C::SimulatorCore::Ptr simulator = TyrantCache::Configuration::Configuration::constructCore();
            // the cache
            Cache::DiskBackedCache::Ptr cache = Cache::DiskBackedCache::Ptr(
                new Cache::DiskBackedCache(simulator)
            );
            
            this->simulator = cache;
        }

        RunCommand::~RunCommand()
        {
        }

        int RunCommand::execute() {
            C::SimulationResult r = this->simulator->simulate(this->task);
            std::cout << "Games played:                    " << std::setw(11) << r.numberOfGames
                      << std::endl;
            std::cout << "Games won:                       " << std::setw(11) << r.gamesWon
                      << " " << r.getWinRate() << std::endl;
            std::cout << "Games lost:                      " << std::setw(11) << r.gamesLost
                      << " " << r.getLossRate() << std::endl;
            std::cout << "Games stalled:                   " << std::setw(11) << r.gamesStalled
                      << " " << r.getStallRate() << std::endl;
            std::cout << "Points for attacker on manual: " << std::setw(13) << r.pointsAttacker
                      << " " << r.getManualANPAttacker() << std::endl;
            std::cout << "Points for attacker on auto:   " << std::setw(13) << r.pointsAttackerAuto
                      << " " << r.getAutoANPAttacker() << std::endl;
            std::cout << "Points for defender on manual: " << std::setw(13) << r.pointsDefender
                      << " " << r.getManualANPDefender() << std::endl;
            std::cout << "Points for defender on auto:   " << std::setw(13) << r.pointsDefenderAuto
                      << " " << r.getAutoANPDefender() << std::endl;
            return 0;
        }

        void
        RunCommand::abort()
        {
            this->simulator->abort();
        }

    }
}
