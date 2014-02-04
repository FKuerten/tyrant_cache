#include "tyrantOptimizerBinding.h++"
#include <errorHandling/assert.h++>
#include <pstreams/pstream.h>
#include <sstream>
#include <iostream>
#include <string>
#include <tuple>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/regex.hpp>
#include <boost/lexical_cast.hpp>

std::string const executable = "./tyrant_optimize";

namespace TyrantCache {
    namespace TO {

        std::string
        TyrantOptimizerCLI::getCoreVersion() const
        {
            redi::ipstream in(executable + " -version");
            std::stringstream ss;
            std::string str;
            while(std::getline(in, str)) {
                ss << str << std::endl;
            }
            std::string result = ss.str();
            boost::algorithm::trim(result);
            return result;
        }

        std::string
        TyrantOptimizerCLI::getCoreVersionHumanReadable() const
        {
            return this->getCoreVersion();
        }

        std::string
        TyrantOptimizerCLI::getCoreName() const
        {
            return executable;
        }

        std::tuple<std::string, bool>
        deckTemplateToTOArgument(C::DeckTemplate::Ptr)
        {
            throw 0;
        }

        C::SimulationResult
        TyrantOptimizerCLI::simulate(C::SimulationTask const & task)
        {
            assertX(!this->theProgram.is_open());

            // A Build the command:
            std::stringstream command;

            // A.0 We start with the executable.
            command << executable;
                        
            // A.10 the decks
            // TODO need something more standardized than passing literal input values
            // TODO also order
            std::tuple<std::string, bool> attackerInformation = deckTemplateToTOArgument(task.attacker);
            std::tuple<std::string, bool> defenderInformation = deckTemplateToTOArgument(task.defender);
            command << " " << std::get<0>(attackerInformation);
            command << " " << std::get<0>(defenderInformation);

            // A.20 the flags
            if (task.achievement > 0) {
                command << " " << "-A" << " " << task.achievement;
            }

            // A.30 the operation
            command << " " << "sim";
            // A.31 the number of iterations
            command << " " << task.minimalNumberOfGames;
            // A.32 surge
            if (task.surge) {
                command << " " << "-s";
            }
            // A.33 ordered decks
            if (std::get<1>(attackerInformation)) {
                command << " " << "-r";
            }
            if (std::get<1>(defenderInformation)) {
                throw LogicError("Tyrant Optimize binding does not support ordered defense decks.");
            }

            //std::clog << "Arguments: " << std::endl;
            //for(std::string argument: arguments) {
            //    std::clog << '"' << argument << '"' << std::endl;
            //}
            //std::clog << command.str();
            //std::clog << std::endl;
            //std::clog << "Result: " << std::endl;
            //this->theProgram.open(executable, arguments);
            this->theProgram.open(command.str());

            std::stringstream ssResult;
            std::string line;
            while(std::getline(this->theProgram, line)) {
                ssResult << line << std::endl;
                //std::clog << line << std::endl;
            }
            this->theProgram.close();
            int exitCode = this->theProgram.rdbuf()->status();
            //std::clog << "exit code: " << exitCode << std::endl;

            if (exitCode != 0) {
                std::stringstream ssMessage;
                ssMessage << "Simulation failed. Reason:" << std::endl;
                ssMessage << ssResult.str();
                throw RuntimeError(ssMessage.str());
            }

            std::clog << std::endl;

            // Parse the result
            C::SimulationResult simulationResult;
            while(std::getline(ssResult, line)) {
                if (boost::starts_with(line, "win%: ")) {
                    boost::smatch match;
                    std::string sRegex = "win%: (.+) \\((.+) / (.+)\\)";
                    boost::regex regex{sRegex};
                    if (boost::regex_match(line, match, regex)) {
                        simulationResult.gamesWon = boost::lexical_cast<unsigned int>(match.str(2));
                    } 
                } else if (boost::starts_with(line, "stall%: ")) {
                    boost::smatch match;
                    std::string sRegex = "stall%: (.+) \\((.+) / (.+)\\)";
                    boost::regex regex{sRegex};
                    if (boost::regex_match(line, match, regex)) {
                        simulationResult.gamesStalled = boost::lexical_cast<unsigned int>(match.str(2));
                    }
                } else if (boost::starts_with(line, "loss%: ")) {
                    boost::smatch match;
                    std::string sRegex = "loss%: (.+) \\((.+) / (.+)\\)";
                    boost::regex regex{sRegex};
                    if (boost::regex_match(line, match, regex)) {
                        simulationResult.gamesLost = boost::lexical_cast<unsigned int>(match.str(2));
                    }                    
                }
                simulationResult.numberOfGames = simulationResult.gamesWon
                                               + simulationResult.gamesStalled
                                               + simulationResult.gamesLost;
            }
            //std::clog << std::flush;
            return simulationResult;
        }
        
        void
        TyrantOptimizerCLI::abort()
        {
            this->theProgram.rdbuf()->kill(SIGINT);
        }

    }
}
