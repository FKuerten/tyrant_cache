#ifndef TYRANT_CACHE_CONFIGURATION_CONFIGURATION_HPP
    #define TYRANT_CACHE_CONFIGURATION_CONFIGURATION_HPP

    #include "../core/simulatorCore.h++"

    namespace Core = TyrantCache::Core;
    namespace TyrantCache {
        namespace Configuration {

            class Configuration {
                public:
                    static Core::SimulatorCore::Ptr constructCore();
            };
        }
    }
#endif
