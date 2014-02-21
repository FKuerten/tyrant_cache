#ifndef TYRANT_CACHE_CORE_SIMULATORCORE_HPP
    #define TYRANT_CACHE_CORE_SIMULATORCORE_HPP

    // For std::shared_ptr
    #include <memory>
    // For the return of getXMLVersions()
    #include <map>
    #include "simulationResult.h++"
    #include "simulationTask.h++"
        
    namespace Tyrant {
        namespace Core {
                                    
            class SimulatorCore {
                public:
                    typedef std::shared_ptr<SimulatorCore> Ptr;

                public:
                    virtual ~SimulatorCore();
                    virtual SimulationResult simulate(SimulationTask const &) = 0;
                    virtual void abort() = 0;

                    virtual std::string getCoreName() const = 0;
                    virtual std::string getCoreVersion() const = 0;
                    virtual std::string getCoreVersionHumanReadable() const = 0;
                    virtual std::map<std::string,std::string> getXMLVersions() const;
            };
            
        }
    }

#endif
