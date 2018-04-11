//
// Created by Dylan Galea on 07/04/2018.
//

/**
 * This class is created in order to be used in the definition function parameters. Thus this will not be one of the ASTNodes.
 */

#ifndef COMPILERSASSIGNMENT_FORMALPARAM_H
#define COMPILERSASSIGNMENT_FORMALPARAM_H

#include <string>
#include "../Type.h"
#include "../Expression/ASTIdentifierExprNode.h"

using namespace std;

namespace AST{
    class FormalParam {
    private:
        ASTIdentifierExprNode *identifier; //stores the address of the identifier in the function definition
        Type type; // stores the type of the identifier in the function definition parameter.
    public:
        /**
         * This constructor is used to create a formal parameter , initializing this->identifier,type to @param ident,type
         * respectively
         * @param ident
         * Contains the address of the ASTIdentifierNode expression that will be assigned to this->identifier
         * @param type
         * Contains the type of the identifier to be assigned to this->type
         */
        FormalParam(ASTIdentifierExprNode *ident,Type type);
        /**
         * This setter is used to give a value to this->identifier
         * @param ident
         * Stores the address of the identifier to be assigned to this->identifier
         */
        void setIdentifier(ASTIdentifierExprNode *ident);
        /**
         * This setter is used to give a value to this->type
         * @param type
         * Stores the type to be assigned to this->type
         */
        void setType(Type type);
        /**
         * This getter is used to return the pointer this->identifier
         * @return
         * The pointer this->identifier
         */
        ASTIdentifierExprNode* getIdentifier();
        /**
         * The getter is used to return the value stored in type
         * @return
         * The value in type of Type.
         */
        Type getType();
    };
}
#endif //COMPILERSASSIGNMENT_FORMALPARAM_H
