#ifndef TYRANT_CACHE_CLI_CONFIGURATION_HPP
    #define TYRANT_CACHE_CLI_CONFIGURATION_HPP

    #include "../core/simulatorCore.h++"

    namespace Core = TyrantCache::Core;
    namespace TyrantCache {
        namespace CLI {

            class Configuration {
                public:
                    Core::SimulatorCore::Ptr constructCore();
                    signed int verbosity = 0;
            };
        }
    }
#endif
