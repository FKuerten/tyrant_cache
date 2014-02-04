#include "optionParser.h++"

/*
#include <boost/lexical_cast.hpp>
#include <boost/program_options/errors.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>
#include <cctype>
#include <cstddef>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>
*/

#include "../errorHandling/exceptions.h++"
#include "runCommand.h++"
/*
#include "../CORE/achievementOptions.hpp"
#include "../CORE/activeDeck.forward.hpp"
#include "../CORE/assert.hpp"
#include "../CORE/autoDeckTemplate.hpp"
#include "../CORE/cardDB.hpp"
#include "../CORE/constants.hpp"
#include "../CORE/deckTemplate.hpp"
#include "../CORE/iterateDecksCore.hpp"
#include "../CORE/questDeck.hpp"
#include "../CORE/raidDeck.hpp"
#include "../CORE/simpleTypes.hpp"
#include "missionIdDeckTemplate.hpp"

#include "simpleOrderedDeckTemplate.hpp"
#include "../CORE/multiDeckTemplate.hpp"
#include "../OPT/optimizer.hpp"

#include "deckParser.hpp"
*/

namespace po = boost::program_options;
namespace TyrantCache {
    namespace CLI {

        Command::Ptr parseArguments(int argc
                                   ,char const * const * argv
                                   )
        {
            try {
                Configuration configuration;
                unsigned int numberOfIterations;
                std::string attacker, defender;
                bool surge;
                int battleGroundId;
                int achievementId;
                bool cacheRead = true;
                bool cacheWrite = true;
                bool useRaidRules;
                int verbosity;

                po::options_description desc("Allowed options");
                desc.add_options()
                    ("help,h", "produce help message")
                    ("version,V", "version information")
                    ("core-version", "version of the core")
                    ("verbose,v", "increase verbosity")
                    ("number-of-iterations,n"
                    ,po::value<unsigned int>(&numberOfIterations)->default_value(1000)
                    ,"specify the total number of iterations"
                    )
                    ("attacker"
                    ,po::value<std::string>(&attacker)->default_value(std::string())
                    ,"the attacker"
                    )
                    ("defender"
                    ,po::value<std::string>(&defender)->default_value(std::string())
                    ,"the defender"
                    )
                    ("surge"
                    ,po::bool_switch(&surge)->default_value(false)
                    ,"simulate surge (defender goes first)"
                    )
                    ("battleground-id"
                    ,po::value<int>(&battleGroundId)->default_value(-1)
                    ,"set the battleground to use"
                    )
                    ("achievement-id"
                    ,po::value<int>(&achievementId)->default_value(-1)
                    ,"id of the achievement to check"
                    )                   
                    ("cache-read"
                    ,po::bool_switch(&cacheRead)
                    ,"read from the cache"
                    )
                    ("no-cache-read"
                    ,po::value<bool>(&cacheRead)->implicit_value(false)->zero_tokens()
                    ,"do not read from the cache"
                    )
                    ("raid-rules"
                    ,po::bool_switch(&useRaidRules)->default_value(false)
                    ,"use raid rules"
                    )
                ;

                po::variables_map vm;
                po::store(po::parse_command_line(argc, argv, desc), vm);

                if (vm.count("help")) {
                    return Command::Ptr(new HelpCommand(configuration, desc));
                } else if (vm.count("core-version")) {
                    return Command::Ptr(new CoreVersionCommand(configuration));
                } else if (vm.count("version")) {
                    return Command::Ptr(new VersionCommand(configuration));
                }

                po::notify(vm);
                
                // check some argument relation
                if (attacker.empty()) {
                    throw InvalidUserInputError("Need an attacker.");
                } else if (defender.empty()) {
                    throw InvalidUserInputError("Need a defender.");
                }

                verbosity = vm.count("verbose");

                RunCommand::Ptr command = RunCommand::Ptr(
                    new RunCommand(configuration)                                    
                );
                command->setCacheRead (cacheRead);
                command->setCacheWrite(cacheWrite);

                command->task.minimalNumberOfGames = numberOfIterations;
                if (!attacker.empty()) {
                    command->task.attacker = attacker;
                }
                if (!defender.empty()) {
                    command->task.defender = defender;
                }
                command->task.surge = surge;
                command->task.battleGround = battleGroundId;
                command->task.numberOfRounds = !useRaidRules ? 50 : 30;                
                command->task.useRaidRules = useRaidRules;
                command->task.achievement = achievementId;
                return command;
             } catch (boost::program_options::required_option &e) {
                 std::stringstream ssMessage;
                 ssMessage << "Error parsing the arguments:" << std::endl;
                 ssMessage << e.what() << std::endl;
                 throw InvalidUserInputError(ssMessage.str());
             }
        }

    }
}
