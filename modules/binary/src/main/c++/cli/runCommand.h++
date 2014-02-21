#ifndef TYRANT_CACHE_CLI_RUNCOMMAND_HPP
    #define TYRANT_CACHE_CLI_RUNCOMMAND_HPP

    #include <core/simulatorCore.h++>
    #include "../cache/diskBackedCache.h++"
    #include "commands.h++"
    #include <memory>

    namespace Core = Tyrant::Core;
    namespace Cache = TyrantCache::Cache;
    namespace TyrantCache {
        namespace CLI {

            class RunCommand : public Command {
                public:
                    typedef std::shared_ptr<RunCommand> Ptr;
                public:
                    Core::SimulationTask task;
                private:
                    Cache::DiskBackedCache::Ptr simulator;
                public:
                    void setCacheWrite(bool cacheWrite);
                    void setCacheRead(bool cacheRead);
                public:
                    RunCommand(Configuration);
                    ~RunCommand();

                    int execute();
                    void abort();
            };
        }
    }

#endif
