#include "simulationResult.h++"

namespace TyrantCache {
    namespace Core {

        SimulationResult::SimulationResult()
        : numberOfGames(0)
        , gamesWon(0)
        , gamesStalled(0)
        , gamesLost(0)
        , pointsAttacker(0)
        , pointsAttackerAuto(0)
        , pointsDefender(0)
        , pointsDefenderAuto(0)
        {
        }

        SimulationResult &
        SimulationResult::operator+=(SimulationResult const & rhs)
        {
            this->numberOfGames      += rhs.numberOfGames;
            this->gamesWon           += rhs.gamesWon;
            this->gamesStalled       += rhs.gamesStalled;
            this->gamesLost          += rhs.gamesLost;
            this->pointsAttacker     += rhs.pointsAttacker;
            this->pointsAttackerAuto += rhs.pointsAttackerAuto;
            this->pointsDefender     += rhs.pointsDefender;
            this->pointsDefenderAuto += rhs.pointsDefenderAuto;
            return *this;
        }

        SimulationResult const
        operator+(SimulationResult const & lhs
                 ,SimulationResult const & rhs
                 )
        {
            SimulationResult tmp(lhs);
            tmp += rhs;
            return tmp;
        }

        double
        SimulationResult::getWinRate() const
        {
            return static_cast<double>(this->gamesWon) / static_cast<double>(this->numberOfGames);
        }

        double
        SimulationResult::getLossRate() const
        {
            return static_cast<double>(this->gamesLost) / static_cast<double>(this->numberOfGames);
        }

        double
        SimulationResult::getStallRate() const
        {
            return static_cast<double>(this->gamesStalled) / static_cast<double>(this->numberOfGames);
        }

        double
        SimulationResult::getAutoANPAttacker() const
        {
            return static_cast<double>(this->pointsAttackerAuto) / static_cast<double>(this->numberOfGames);
        }

        double
        SimulationResult::getAutoANPDefender() const
        {
            return static_cast<double>(this->pointsDefenderAuto) / static_cast<double>(this->numberOfGames);
        }

        double
        SimulationResult::getManualANPAttacker() const
        {
            return static_cast<double>(this->pointsAttacker) / static_cast<double>(this->numberOfGames);
        }

        double
        SimulationResult::getManualANPDefender() const
        {
            return static_cast<double>(this->pointsDefender) / static_cast<double>(this->numberOfGames);
        }

