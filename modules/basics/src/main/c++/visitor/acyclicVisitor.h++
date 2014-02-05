#ifndef TYRANT_CACHE_VISITOR_ACYCLICVISITOR_HPP
    #define TYRANT_CACHE_VISITOR_ACYCLICVISITOR_HPP

    namespace TyrantCache {
        namespace Visitor {

            class AcyclicVisitor {
                public:
                    virtual ~AcyclicVisitor();
            };
            
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
    ClassName::accept(::TyrantCache::Visitor::AcyclicVisitor & visitor) \
    { \
        if (ClassName::Visitor* correctVisitor = dynamic_cast<ClassName::Visitor*>(&visitor)) { \
            correctVisitor->visit(*this); \
        } else { \
            throw ::TyrantCache::Visitor::NoSuchVisitorException(); \
        } \
    }

    
#endif
