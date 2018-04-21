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
#include "../../ASTHierarchy/Statement/ASTBlockStatementNode.h"

using namespace AST;
#include <iostream>
using namespace std;

namespace Visitors{
    class TypeBinder {
    public:
        /**
         * The valueInIdentifier struct was created , so that in the interpreter execution pass , the value associated
         * with an identifier can be stored. Thus if the identifier is of type 'a' , then the container of type 'a'
         * in the struct would contain that value.
         */
        struct valueInIdentifier{
            bool boolValue;
            int intValue;
            double realValue;
            string stringValue;
        };
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
        /**
         * This method is used to give a value to the integer field in the private struct valueInIdentifier
         * @param value
         * Stores the integer value to be assigned to the integer field in the private struct valueInIdentifier
         */
        void setIntValue(int value);
        /**
         * This method is used to give a value to the function block associated with a function identifier
         * @param value
         * Stores the address of the function block that will be assigned to this->FnDefnBlock
         */
        void setFnDefnBlock(ASTBlockStatementNode* value);
        /**
         * This method is used to give a value to the real field in the private struct valueInIdentifier
         * @param value
         * Stores the real value to be assigned to the real field in the private struct valueInIdentifier.
         */
        void setRealValue(double value);
        /**
         * This method is used to give a value to the string field in the private struct valueInIdentifier
         * @param value
         * Stores the string value to be assigned to the string field in the private struct valueInIdentifier
         */
        void setStringValue(string value);
        /**
         * This method is used to give a value to the bool field in the private struct valueInIdentifier
         * @param value
         * Stores the bool value to be assigned to the string field in the private struct valueInIdentifier
         */
        void setBoolValue(bool value);
        /**
         * This method is used to get the pointer pointing to the valueInIdentifier struct instance.
         * @return
         * The pointer of type valueInIdentifier that stores the address of the struct instance storing the value corresponding
         * to the identifier.
         */
        valueInIdentifier* getValueInIdentifier();
        /**
         * This method is used to get the pointer pointing to the block associated with the function identifier
         * @return
         * The pointer pointing to the block associated with the function identifier.
         */
        ASTBlockStatementNode* getFnDefnBlock();
        /**
         * This method is used to give a value of type FormalParams to the private field this->formalParams
         * @param fp
         * Stores the address of the FormalParam value that will be pointed to this.formalParams.
         */
        void setFormalParams(FormalParams* fp);
        /**
         * This method is used to return the pointer this.formalParams
         * @return
         * The pointer of type FormalParams , this->formalParams.
         */
        FormalParams* getFormalParams();

        /**
         * This method gets the string representation of the binded type .. thus it returns function or variable
         * @return
         * String which is "function" if we are binding a function , or "variable" if we are binded a variable
         */

        string getStringRepresentationOfIdentifierType();
    private:
        Type primitiveType; //Stores the identifier's declared type in minilang
        IdentifierType identifierType; // stores whether the identifier name is set to a function or a variable.
        valueInIdentifier *value; //stores the address of the value struct
        ASTBlockStatementNode *FnDefnBlock; // stores the address of the function block associated with an identifier
        FormalParams* formalParams; // stores the address of the parameters associated with the function declaration
    };
}

#endif //COMPILERSASSIGNMENT_TYPEBINDER_H
