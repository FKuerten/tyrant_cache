#include "commands.h++"
#include <version.h++>
#include <core/simulatorCore.h++>
#include <errorHandling/assert.h++>

namespace C = Tyrant::Core;
namespace TyrantCache {
    namespace CLI {

        Command::Command(Configuration configuration)
        : aborted(false)
        , configuration(configuration)
        {}

        Command::~Command()
        {}

        void
        Command::abort()
        {
            this->aborted = true;
        }

        VersionCommand::VersionCommand(Configuration configuration)
        : Command(configuration)
        {
        }

        int VersionCommand::execute()
        {
            //human readable
            std::cout << "human readable version description:" << std::endl;
            std::cout << "\t" << tyrantCache_VERSION_DESCRIBE;
            if (tyrantCache_DIRTY_HEAD) {
                std::cout << "+";
                std::cout << tyrantCache_DIRTY_HASH;
            }
            std::cout << std::endl;

            // commit-ish
            std::cout << "tyrantCache version hash:" << std::endl;
            std::cout << '\t' << tyrantCache_VERSION;
            if (tyrantCache_DIRTY_HEAD) {
                std::cout << "+";
                std::cout << tyrantCache_DIRTY_HASH;
            }
            std::cout << std::endl;

            // tags
            if (!tyrantCache_DIRTY_HEAD) {
                std::cout << "Tags pointing at this version: " << std::endl;
                std::cout << '\t' << tyrantCache_VERSION_TAGS << std::endl;
            }

            // TODO Obviously if we want to allow exchangable core we would need a better way here.
            C::SimulatorCore::Ptr core = this->configuration.constructCore();

            std::cout << "Simulator core name: "    << std::endl;
            std::cout << '\t' << core->getCoreName()        << std::endl;
            std::cout << "Simulator core version: " << std::endl;
            std::cout << '\t' << core->getCoreVersion()     << std::endl;

            std::cout << "XML data version: "       << std::endl;
            std::map<std::string,std::string> xmlHashes = core->getXMLVersions();
            assertGT(xmlHashes.size(),static_cast<std::size_t>(0u));
            for(std::map<std::string,std::string>::const_iterator iter = xmlHashes.begin()
               ;iter != xmlHashes.end()
               ;iter++
               )
            {
                std::cout << '\t';
                std::cout << std::setw(20) << std::left << iter->first << " ";
                std::cout << iter->second << std::endl;
            }
            return 0;
        }

        CoreVersionCommand::CoreVersionCommand(Configuration configuration)
        : Command(configuration)
        {
        }

        int CoreVersionCommand::execute()
        {
            C::SimulatorCore::Ptr core = this->configuration.constructCore();

            std::cout << core->getCoreVersionHumanReadable() << std::endl;
            return 0;
        }

        HelpCommand::HelpCommand(Configuration configuration, boost::program_options::options_description const & desc)
        : Command(configuration)
        , desc(desc)
        {
        }

        int HelpCommand::execute()
        {
            std::cout << this->desc << std::endl;
            return 0;
        }

    }
}
