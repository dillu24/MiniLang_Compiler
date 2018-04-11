//
// Created by Dylan Galea on 06/04/2018.
//
/**
 * This class is used to encode a node that is created whenever the parser matches the production rule related to variable
 * declaration . This concrete class is a child of ASTStatementNode and thus it contains all methods and variables related to
 * the enum StatementType which is inherited . It also must implement the accept method which was virtual in parent classes.
 * As children node this class has 2 children branches , one which stores the expression that the variable will be assigned
 * to , and the other stores the identifier name . Alond with the children nodes , this class also stores information related
 * to the variable type.
 */
#ifndef COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H

#include <string>
#include "../ASTStatementNode.h"
#include "../Type.h"
#include "../ASTExprNode.h"
#include "../Expression/ASTIdentifierExprNode.h"

using namespace std;
namespace AST{
    class ASTVarDeclStatementNode:public ASTStatementNode{
    private:
        ASTIdentifierExprNode *identifier; //stores the address of the child node containing the variable name.
        Type type; //Stores the type of the variable
        ASTExprNode* expression; // stores the address of the child node containing the expression the variable will be assigned to
    public:
        /**
         * This constructor is used to create a new ASTVarDeclStatementNode having no children attached to it , but initializing
         *the type of this statement node as required
         */
        ASTVarDeclStatementNode();
        /**
         * This constructor is used to create a new ASTVarDeclStatementNode with children stored in @param identifier,expr.In
         * addition to that the type of the identifier is stored in this node also
         * @param identifier
         * Stores the address of the ASTIdentifierExprNode that will be assigned to this->identifier
         * @param type
         * Stores the type to be assigned to this->type
         * @param expr
         * Stores the address of the ASTExprNode that will be assigned to this->expression
         */
        ASTVarDeclStatementNode(ASTIdentifierExprNode *identifier,Type type,ASTExprNode* expr);
        /**
         * This destructor deletes data related to the ASTVarDeclStatementNode from the heap
         */
        ~ASTVarDeclStatementNode();
        /**
         * This method is used to give a value to this->identifier
         * @param ident
         * Stores the address of the identifier expression node to be assigned to this->identifier
         */
        void setIdentifier(AST::ASTIdentifierExprNode *ident);
        /**
         * This method is used to give a value to this->type
         * @param type
         * Stores the type to be assigned to this->type
         */
        void setType(Type type);
        /**
         * This method is used to give a value to this->expression
         * @param expr
         * Stores the address of the expression node to be assigned to this->expression
         */
        void setExpr(ASTExprNode* expr);
        /**
         * This getter is used to return the value of the private variable this->identifier
         * @return
         * The identifier pointer this->identifier
         */
        ASTIdentifierExprNode* getIdentifier();
        /**
         * This getter is used to return the value of the private variable this->type
         * @return
         * A value of type Type stored in this->type
         */
        Type getType();
        /**
         * This getter is used to return the value of the private variable this->expression
         * @return
         * The pointer this->expression
         */
        ASTExprNode* getExpr();
        /**
         * This is the implementation of the virtual inherited method from the parents
         * @param v
         * Stores the address of the visitor visiting this node.
         */
        void accept(Visitor *v) override;
    };
}


#endif //COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H
