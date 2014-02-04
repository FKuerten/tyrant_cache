#ifndef TYRANT_CACHE_CLI_OPTIONPARSER_HPP
    #define TYRANT_CACHE_CLI_OPTIONPARSER_HPP

    //#include "../core/simulatorCore.hpp"
    #include "commands.h++"

    namespace TyrantCache {
        namespace CLI {

            Command::Ptr parseArguments(int argc, char const * const * argv);

        }
    }

#endif
