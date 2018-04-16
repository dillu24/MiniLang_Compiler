//
// Created by Dylan Galea on 14/04/2018.
//

/**
 * This class is used to encode the type information needed to be mapped to the key value of the hash map forming
 * the symbol table for a particular scope. This class gives the information whether an identifier is binded to
 * an function , or to a variable . If it is binded to a function , then the parameterTypes vector must contain the
 * types of the parameters that have make up the function definition . In this way the visitor class SemanticAnalysis
 * finds it easy to check that when a function call happens , the parameters passed in the function call have the same
 * type as the function parameter definition. Also this class stores the type of the return value if we are encoding a function
 * or the type of the variable if we are storing a variable.
 */

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
        vector<Type> parameterTypes; //This vector stores the parameter types , if a function is binded to the identifier name
        enum IdentifierType{ // this enum indicates whether the identifier name is binded to a function or to a variable
            FUNCTION,
            VARIABLE
        };
        /**
         * This constructor is used to create a new TypeBinder instance given the primitive type and the identifier type
         * @param primitiveType
         * Stores the primitive type of the variable or function being declared
         * @param identifierType
         * Stores a value of type IdentifierType , indicating whether we are storing a function or an identifier.
         */
        TypeBinder(Type primitiveType,IdentifierType identifierType);
        /**
         * This method is used to return the private variable primitiveType
         * @return
         * The value of type Type stored in primitiveType.
         */
        Type getPrimitiveType();
        /**
         * This method is used to return the private variable identifierType
         * @return
         * The value of type IdentifierType stored in identifierType.
         */
        IdentifierType getIdentifierType();
        /**
         * This method is used to set a value to the private variable identifierType
         * @param identifierType
         * Stores the value of type IdentifierType to be assigned to the private variable identifierType
         */
        void setIdentifierType(IdentifierType identifierType);
        /**
         * This method is used to set a value to the private variable primitiveType
         * @param type
         * Stores the value of type Type to be assigned to the private variable identifierType.
         */
        void setPrimitiveType(Type type);
        /**
         * This method is used to return the keyword representation of the primitive type
         * @return
         * A string value representing the keyword of the primitive type.
         */
        string getStringRepresentationOfPrimitiveType();
    private:
        Type primitiveType; //Stores the identifier's declared type in minilang
        IdentifierType identifierType; // stores whether the identifier name is set to a function or a variable.
    };
}

#endif //COMPILERSASSIGNMENT_TYPEBINDER_H
