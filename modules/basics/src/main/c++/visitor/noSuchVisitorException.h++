#ifndef PRAETORIAN_BASICS_VISITOR_NOSUCHVISITOREXCEPTION_HPP
    #define PRAETORIAN_BASICS_VISITOR_NOSUCHVISITOREXCEPTION_HPP

    #include "../errorHandling/exceptions.h++"

    namespace Praetorian {
        namespace Basics {
            namespace Visitor {

                class NoSuchVisitorException : public LogicError {
                    public:
                        NoSuchVisitorException();
                };

            }
        }
    }

#endif
