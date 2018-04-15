//
// Created by Dylan Galea on 14/04/2018.
//

#ifndef COMPILERSASSIGNMENT_TYPEBINDER_H
#define COMPILERSASSIGNMENT_TYPEBINDER_H
#include "../../ASTHierarchy/Type.h"
#include "../../ASTHierarchy/Statement/FormalParams.h"

using namespace AST;
#include <iostream>
using namespace std;

namespace Visitors{
    class TypeBinder {
    public:
        vector<Type> parameterTypes;
        enum IdentifierType{
            FUNCTION,
            VARIABLE
        };
        TypeBinder(Type primitiveType,IdentifierType identifierType);
        Type getPrimitiveType();
        IdentifierType getIdentifierType();
        void setIdentifierType(IdentifierType identifierType);
        void setPrimitiveType(Type type);
        string getStringRepresentationOfPrimitiveType();
    private:
        Type primitiveType;
        IdentifierType identifierType;
    };
}

#endif //COMPILERSASSIGNMENT_TYPEBINDER_H
