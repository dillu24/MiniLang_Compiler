//
// Created by Dylan Galea on 06/04/2018.
//

/**
 * This class is used to encode the AST return statement node  which is created whenever the parser successfully matches
 * the production rule related to return statements. This is a concrete child class of ASTStatementNode and thus it contains
 * the getter,setter and statementType variable related to the enum StatementType and the accept method implementation .
 * This node also has a child ASTExprNode attached to it that stores the expression to be returned . Since this expression
 * is declared as private , getters and setters had to be designed.
 */

#ifndef COMPILERSASSIGNMENT_ASTRETURNSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTRETURNSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"

namespace AST{
    class ASTReturnStatementNode:public ASTStatementNode {
    private:
        ASTExprNode* expression; //stores the address of the expression child node attached to ASTReturnStatementNode
    public:
        /**
         * The constructor used to create a new ASTReturnStatementNode and storing the value of @param expr in
         * this->expression
         * @param expr
         * Stores the address of the ASTExprNode that will be assigned to this->expression
         */
        explicit ASTReturnStatementNode(ASTExprNode* expr);
        /**
         * The destructor used to delete the data related to ASTReturnStatementNode from the heap
         */
        ~ASTReturnStatementNode();
        /**
         * The setter method used to give a value to the private variable this->expression
         * @param expr
         * Stores the address of the expression node that will be assigned to this->expression
         */
        void setExpression(ASTExprNode* expr);
        /**
         * The getter method used to return the pointer this->expression
         * @return
         * An ASTExprNode pointer storing the adress of the expression attached to ASTReturnStatementNode
         */
        ASTExprNode* getExpression();
        /**
         * This is the implementation of the virtual function inherited from the parent classes.
         * @param v
         * Stores the address of the visitor that is visiting this node
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTRETURNSTATEMENTNODE_H
