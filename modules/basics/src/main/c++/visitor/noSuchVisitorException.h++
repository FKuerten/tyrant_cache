#ifndef TYRANT_CACHE_VISITOR_NOSUCHVISITOREXCEPTION_HPP
    #define TYRANT_CACHE_VISITOR_NOSUCHVISITOREXCEPTION_HPP

    #include "../errorHandling/exceptions.h++"

    namespace TyrantCache {
        namespace Visitor {

            class NoSuchVisitorException : public LogicError {
                public:
                    NoSuchVisitorException();
            };
            
        }
    }
    
#endif
