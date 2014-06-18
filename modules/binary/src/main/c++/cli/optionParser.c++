#include "optionParser.h++"

#include <boost/program_options/parsers.hpp>
//#include <boost/program_options/value_semantic.hpp>
#include <boost/program_options/variables_map.hpp>

#include <errorHandling/exceptions.h++>
#include "runCommand.h++"
#include "deckParser.h++"

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
                bool attackerFromStdIn, defenderFromStdIn;
                bool surge;
                int battleGroundId;
                int achievementId;
                bool cacheRead;
                bool cacheWrite;
                bool useRaidRules;

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
                    ("attacker-from-stdin"
                    ,po::bool_switch(&attackerFromStdIn)->default_value(false)
                    ,"read attacker decks from stdin"
                    )
                    ("defender"
                    ,po::value<std::string>(&defender)->default_value(std::string())
                    ,"the defender"
                    )
                    ("defender-from-stdin"
                    ,po::bool_switch(&defenderFromStdIn)->default_value(false)
                    ,"read defender decks from stdin"
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
                    ,po::bool_switch(&cacheRead)->default_value(true)
                    ,"read from the cache"
                    )
                    ("no-cache-read"
                    ,po::value<bool>(&cacheRead)->implicit_value(false)->zero_tokens()
                    ,"do not read from the cache"
                    )
                    ("cache-write"
                    ,po::bool_switch(&cacheWrite)->default_value(true)
                    ,"write to the cache"
                    )
                    ("no-cache-write"
                    ,po::value<bool>(&cacheWrite)->implicit_value(false)->zero_tokens()
                    ,"do not write to the cache"
                    )
                    ("raid-rules"
                    ,po::bool_switch(&useRaidRules)->default_value(false)
                    ,"force use of raid rules (default: raid rules will be used if one deck is a raid deck)"
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

                //std::clog << "cache-read:  " << cacheRead << std::endl;
                //std::clog << "cache-write: " << cacheWrite << std::endl;

                // check some argument relation
                if (attacker.empty() && !attackerFromStdIn) {
                    throw InvalidUserInputError("Need an attacker.");
                } else if (defender.empty() && !defenderFromStdIn) {
                    throw InvalidUserInputError("Need a defender.");
                } else if (!attacker.empty() && attackerFromStdIn) {
                    throw InvalidUserInputError("Can not supply both --attacker and --attacker-from-stdin.");
                } else if (!defender.empty() && defenderFromStdIn) {
                    throw InvalidUserInputError("Can not supply both --defender and --defender-from-stdin.");
                }

                // We may lose value here, but seriously, who is going to request verbosity more than maxint times?
                configuration.verbosity = static_cast<int>(vm.count("verbose"));

                RunCommand::Ptr command = RunCommand::Ptr(
                    new RunCommand(configuration)
                );
                command->setCacheRead (cacheRead);
                command->setCacheWrite(cacheWrite);
                command->attackerFromStdIn = attackerFromStdIn;
                command->defenderFromStdIn = defenderFromStdIn;

                command->task.minimalNumberOfGames = numberOfIterations;
                if (!attacker.empty()) {
                    command->task.attacker = parseDeck(attacker);
                }
                if (!defender.empty()) {
                    command->task.defender = parseDeck(defender);
                }
                command->task.surge = surge;
                command->task.battleGround = battleGroundId;
                command->task.numberOfRounds = -1;
                if (useRaidRules) {
                    command->task.useRaidRules = Core::tristate::TRUE;
                }
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
