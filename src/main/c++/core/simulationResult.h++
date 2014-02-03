#ifndef TYRANT_CACHE_CORE_SIMULATIONRESULT_HPP
    #define TYRANT_CACHE_CORE_SIMULATIONRESULT_HPP

    namespace TyrantCache {
        namespace Core {

            struct SimulationResult {
                unsigned long numberOfGames;
                unsigned long gamesWon;
                unsigned long gamesStalled;
                unsigned long gamesLost;

                // Here we store points by player
                unsigned long pointsAttacker;
                unsigned long pointsAttackerAuto;
                unsigned long pointsDefender;     //< hardly meaningful: the only time we have a manual defender is in live pvp where damage does not matter.
                unsigned long pointsDefenderAuto;

                // TODO Achievement?

                SimulationResult();

                SimulationResult & operator+=(SimulationResult const & rhs);

                double getWinRate() const;
                double getLossRate() const;
                double getStallRate() const;
                double getAutoANPAttacker() const;
                double getAutoANPDefender() const;
                double getManualANPAttacker() const;
                double getManualANPDefender() const;
            };

            SimulationResult const operator+(SimulationResult const & lhs, SimulationResult const & rhs);
            
        }
    }
#endif
