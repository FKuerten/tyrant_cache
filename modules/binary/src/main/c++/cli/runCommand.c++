#include "runCommand.h++"

#include "configuration.h++"
#include "../cache/diskBackedCache.h++"
#include <iomanip>
#include "deckParser.h++"
#include <errorHandling/assert.h++>

namespace Core = Tyrant::Core;
namespace Cache = TyrantCache::Cache;
namespace TyrantCache {
    namespace CLI {

        RunCommand::RunCommand(Configuration configuration
                              )
        : Command(configuration)
        , attackerFromStdIn(false)
        , defenderFromStdIn(false)
        , aborted(false)
        {
            // the core
            C::SimulatorCore::Ptr simulator = configuration.constructCore();
            // the cache
            Cache::DiskBackedCache::Ptr cache = Cache::DiskBackedCache::Ptr(
                new Cache::DiskBackedCache(simulator)
            );

            this->simulator = cache;
        }

        RunCommand::~RunCommand()
        {
        }

        int RunCommand::execute()
        {
            if (this->attackerFromStdIn || this->defenderFromStdIn) {
                if (this->configuration.verbosity == 0) {
                    std::cout << std::left
                              << std::setw(20) << "attacker deck" << " "
                              << std::setw(20) << "defender deck" << " "
                              << std::setw(10) << "games won" << " "
                              << std::setw(10) << "stalled" << " "
                              << std::setw(10) << "games lost" << " "
                              << std::setw(13) << "points att" << " "
                              << std::setw(13) << "points att a" << " "
                              << std::setw(13) << "points def" << " "
                              << std::setw(13) << "points def a" << " "
                              << std::endl;
                }
                std::string line;
                int returnCode = 0;
                while (std::getline(std::cin, line) && !this->aborted) {
                    Core::SimulationTask task2(this->task);
                    if (this->attackerFromStdIn && this->defenderFromStdIn) {
                        std::stringstream ssLine(line);
                        std::string sDeck1, sDeck2;
                        std::getline(ssLine, sDeck1, ' ');
                        std::getline(ssLine, sDeck2, ' ');
                        task2.attacker = parseDeck(sDeck1);
                        task2.defender = parseDeck(sDeck2);
                    } else if (this->attackerFromStdIn) {
                        task2.attacker = parseDeck(line);
                    } else if (this->defenderFromStdIn) {
                        task2.defender = parseDeck(line);
                    }
                    int subReturnCode = this->simulateSimple(task2);
                    returnCode = returnCode | subReturnCode;
                }
                return returnCode;
            } else {
                return this->simulateSimple(this->task);
            }
        }

        int RunCommand::simulateSimple(Core::SimulationTask const & task)
        {
            assertX(task.attacker);
            assertX(task.defender);
            unsigned int const verbosity = this->configuration.verbosity;
            if (verbosity == 0) {
                std::cout << std::left
                          << std::setw(20) <<  std::string(*task.attacker) << " "
                          << std::setw(20) << std::string(*task.defender) << " "
                          ;
            }

            C::SimulationResult r = this->simulator->simulate(task);

            if (verbosity > 0) {
            std::cout << "                                 " << std::setw(11) << "Count"
                      << " " << std::setw(10) << "avg." << std::endl;
            std::cout << "Games played:                    " << std::setw(11) << r.numberOfGames
                      << std::endl;
            std::cout << "Games won:                       " << std::setw(11) << r.gamesWon
                      << " " << std::setw(10) << std::fixed << std::setprecision(6) << r.getWinRate() << std::endl;
            std::cout << "Games lost:                      " << std::setw(11) << r.gamesLost
                      << " " << std::setw(10) << std::fixed << std::setprecision(6) << r.getLossRate() << std::endl;
            std::cout << "Games stalled:                   " << std::setw(11) << r.gamesStalled
                      << " " << std::setw(10) << std::fixed << std::setprecision(6) << r.getStallRate() << std::endl;
            std::cout << "Points for attacker on manual: " << std::setw(13) << r.pointsAttacker
                      << " " << std::setw(10) << std::fixed << std::setprecision(6) << r.getManualANPAttacker() << std::endl;
            std::cout << "Points for attacker on auto:   " << std::setw(13) << r.pointsAttackerAuto
                      << " " << std::setw(10) << std::fixed << std::setprecision(6) << r.getAutoANPAttacker() << std::endl;
            std::cout << "Points for defender on manual: " << std::setw(13) << r.pointsDefender
                      << " " << std::setw(10) << std::fixed << std::setprecision(6) << r.getManualANPDefender() << std::endl;
            std::cout << "Points for defender on auto:   " << std::setw(13) << r.pointsDefenderAuto
                      << " " << std::setw(10) << std::fixed << std::setprecision(6) << r.getAutoANPDefender() << std::endl;
            } else {
                std::cout << std::right
                          << std::setw(10) << r.gamesWon << " "
                          << std::setw(10) << r.gamesStalled << " "
                          << std::setw(10) << r.gamesLost << " "
                          << std::setw(13) << r.pointsAttacker << " "
                          << std::setw(13) << r.pointsAttackerAuto << " "
                          << std::setw(13) << r.pointsDefender << " "
                          << std::setw(13) << r.pointsDefenderAuto << " "
                          << std::endl;
            }
            return 0;
        }

        void
        RunCommand::abort()
        {
            this->simulator->abort();
            this->aborted = true;
        }

        void
        RunCommand::setCacheRead(bool cacheRead)
        {
            this->simulator->setReadFromCache(cacheRead);
        }

        void
        RunCommand::setCacheWrite(bool cacheWrite)
        {
            this->simulator->setWriteToCache(cacheWrite);
        }

    }
}
