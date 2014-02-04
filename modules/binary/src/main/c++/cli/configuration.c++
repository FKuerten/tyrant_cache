#include "configuration.h++"

#include "../to/tyrantOptimizerBinding.h++"

namespace TyrantCache {
    namespace CLI {

        Core::SimulatorCore::Ptr
        Configuration::constructCore()
        {
            return Core::SimulatorCore::Ptr(
                new TyrantCache::TO::TyrantOptimizerCLI()
            );
        }
    }
}
