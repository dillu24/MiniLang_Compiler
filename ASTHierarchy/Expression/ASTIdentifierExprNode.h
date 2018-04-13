//
// Created by Dylan Galea on 07/04/2018.
//

/**
 * This class is used to encode an Identifier Node , that will be created whenever a parser meets a syntactically
 * correct variable expression .This is a concrete child class of ASTExprNode , thus it must implement the accept
 * virtual method , and contains the getter,setter, expressionType variable related to the enum ExpressionType.
 * Whenever created this node must store the identifier , and since it is private , a number of getters and setters had
 * to be created.
 */
#ifndef COMPILERSASSIGNMENT_ASTIDENTIFEREXPRNODE_H
#define COMPILERSASSIGNMENT_ASTIDENTIFEREXPRNODE_H

#include "../ASTExprNode.h"
#include <string>
using namespace std;

namespace AST{
    class ASTIdentifierExprNode:public ASTExprNode {
    private:
        string identifierName; //Stores the name of the variable,function or function call
    public:
        /**
         * This default constructor is used to give a the type of the Statement.
         */
        ASTIdentifierExprNode();
        /**
         * This constructor is used to initialize a new ASTIdentifierExprNode with the given identifier name. Also
         * in this constructor the inherited variable expressionType is given it's appropiate value.
         * @param identifier
         * Stores the string value that will be stored in the variable this->identifierName"
         */
        explicit ASTIdentifierExprNode(string identifier);
        /**
         * This setter is used to give a value to the private variable "identifierName"
         * @param value
         * Stores the string value that will be assigned to "IdentifierName"
         */
        void setIdentifierName(string value);
        /**
         * The getter method used to get the value stored in "identifierName"
         * @return
         * A string value stored in identifierName
         */
        string getIdentifierName();
        /**
         * The implementation of the virtual method in the parent classes
         * @param v
         * Stores a pointer to a visitor that is going to visit the node
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTIDENTIFEREXPRNODE_H
