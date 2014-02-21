#ifndef TYRANT_CACHE_CLI_RUNCOMMAND_HPP
    #define TYRANT_CACHE_CLI_RUNCOMMAND_HPP

    #include <core/simulatorCore.h++>
    #include "../cache/diskBackedCache.h++"
    #include "commands.h++"
    #include <memory>

    namespace TyrantCache {
        namespace CLI {

            class RunCommand : public Command {
                public:
                    typedef std::shared_ptr<RunCommand> Ptr;

                public:
                    ::Tyrant::Core::SimulationTask task;
                    bool attackerFromStdIn, defenderFromStdIn;

                private:
                    Cache::DiskBackedCache::Ptr simulator;

                public:
                    void setCacheWrite(bool cacheWrite);
                    void setCacheRead(bool cacheRead);

                private:
                    int simulateSimple(::Tyrant::Core::SimulationTask const & task);

                public:
                    RunCommand(Configuration);
                    ~RunCommand();

                    int execute();
                    void abort();
            };
        }
    }

#endif
