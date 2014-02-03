#ifndef TYRANT_CACHE_CLI_RUNCOMMAND_HPP
    #define TYRANT_CACHE_CLI_RUNCOMMAND_HPP

    #include "../core/simulatorCore.h++"
    //#include "../OPT/optimizer.hpp"
    #include "commands.h++"
    //#include <memory>

    namespace C = TyrantCache::Core;
    namespace TyrantCache {
        namespace CLI {

            class RunCommand : public Command {
                public:
                    typedef std::shared_ptr<RunCommand> Ptr;
                public:
                    C::SimulationTask task;
                private:
                    C::SimulatorCore::Ptr simulator;
                public:
                    void setCacheWrite(bool cacheWrite);
                    void setCacheRead(bool cacheRead);
                public:
                    RunCommand(int verbosity);
                    ~RunCommand();

                    int execute();
                    void abort();
            };
        }
    }

#endif
