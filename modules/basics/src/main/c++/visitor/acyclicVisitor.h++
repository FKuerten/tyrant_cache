#ifndef PRAETORIAN_BASICS_VISITOR_ACYCLICVISITOR_HPP
    #define PRAETORIAN_BASICS_VISITOR_ACYCLICVISITOR_HPP

    namespace Praetorian {
        namespace Basics {
            namespace Visitor {

                class AcyclicVisitor {
                    public:
                        virtual ~AcyclicVisitor();
                };

            }
        }
    }

    #include "noSuchVisitorException.h++"

    #define CREATE_VISITOR_INTERFACE(ClassName) \
    class Visitor { \
        public: \
            virtual void visit(ClassName &) = 0; \
            virtual ~Visitor() {}; \
    }

    #define CREATE_VISITOR_METHOD(ClassName) \
    void \
    ClassName::accept(::Praetorian::Basics::Visitor::AcyclicVisitor & visitor) \
    { \
        if (ClassName::Visitor* correctVisitor = dynamic_cast<ClassName::Visitor*>(&visitor)) { \
            correctVisitor->visit(*this); \
        } else { \
            throw ::Praetorian::Basics::Visitor::NoSuchVisitorException(); \
        } \
    }


#endif
