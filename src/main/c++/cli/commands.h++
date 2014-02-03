#ifndef TYRANT_CACHE_CLI_COMMANDS_HPP
    #define TYRANT_CACHE_CLI_COMMANDS_HPP

    // for std::shared_ptr
    #include <memory>
    #include <boost/program_options.hpp>

    namespace TyrantCache {
        namespace CLI {

            class Command {
                private:
                    bool aborted;
                protected:
                    bool isAborted();

                public:
                    typedef std::shared_ptr<Command> Ptr;
                public:
                    Command();
                    virtual ~Command();
                    virtual int execute() = 0;
                    virtual void abort();
            };

            class VersionCommand : public Command {
                public:
                    int execute();
            };

            class CoreVersionCommand : public Command {
                public:
                    int execute();
            };

            class HelpCommand : public Command {
                private:
                    boost::program_options::options_description desc;
                public:
                    HelpCommand(boost::program_options::options_description const & desc);
                    int execute();
            };

        }
    }
#endif
