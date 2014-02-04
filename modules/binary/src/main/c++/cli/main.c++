#include <iostream>
#include "commands.h++"
#include "optionParser.h++"
#include <errorHandling/exceptions.h++>

#ifdef _POSIX_SOURCE
    #include <csignal>
#endif


TyrantCache::CLI::Command::Ptr theCommand;

#ifdef _POSIX_SOURCE
    extern "C" {
        void abortHandler(int sig) {
            // this is evil style, but well...
            theCommand->abort();
        }
    }
#endif

/**
 * Reads cli arguments, parses them, then simulates
 */
int main(int const argc, char * const * const argv)
{
    try {
        TyrantCache::CLI::Command::Ptr command = TyrantCache::CLI::parseArguments(argc, argv);
        
        ::theCommand = command;
        #ifdef _POSIX_SOURCE
            struct sigaction action, oldIntAction, oldTermAction;
            action.sa_handler = &abortHandler;
            //action.sa_sigaction = &abortHandler;
            sigemptyset(&action.sa_mask);
            action.sa_flags = 0;
            sigaction(SIGINT, &action, &oldIntAction);
            sigaction(SIGTERM, &action, &oldTermAction);
            //std::clog << "Signal handlers installed." << std::endl;
        #endif

        command->execute();

        #ifdef _POSIX_SOURCE
            sigaction(SIGINT, &oldIntAction, 0);
            sigaction(SIGTERM, &oldTermAction, 0);
            //std::clog << "Signal handlers removed." << std::endl;
        #endif
        ::theCommand = NULL;

    } catch(Exception const & e) {
        std::cerr << "Exception:" << std::endl;
        std::cerr << e.what() << std::endl;
        e.printStacktrace(std::cerr);
        return -1;
    }
}
