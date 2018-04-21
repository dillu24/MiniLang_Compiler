//
// Created by Dylan Galea on 06/04/2018.
//

/**
 * This class is used to encode the AST print statement node that will be created whenever the parser sucessfully matches
 * the production rule related with the ASTPrintStatementNode. This is a concrete child of the ASTStatement node and thus
 * it contains all the getter,setter and statementType related to the enum statementType along with the accept virtual
 * method. In addition to that ,the ASTPrintStatementNode contains as child the expression node which stores the
 * expression that will be printed.
 */

#ifndef COMPILERSASSIGNMENT_ASTPRINTSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTPRINTSTATEMENTNODE_H

#include "../ASTExprNode.h"
#include "../ASTStatementNode.h"

namespace AST{
    class ASTPrintStatementNode:public ASTStatementNode {
    private:
        ASTExprNode *expression; //Stores the address of the expression child node which stores the expression that will be printed
    public:
        /**
         * Used to create a new ASTPrintStatementNode and storing the value of @param expr in this->expression
         * @param expr
         * Stores the address of the expression node that will be attached as child to the ASTPrintStatementNode
         */
        explicit ASTPrintStatementNode(ASTExprNode* expr);
        /**
         * The destructor used to delete the data related to the ASTPrintStatementNode from the heap
         */
        ~ASTPrintStatementNode();
        /**
         * The setter method used to give a value to this->expression
         * @param expr
         * Stores the address of the expression that will be assigned to this->expression
         */
        void setExpr(ASTExprNode* expr);
        /**
         * The getter method used to get the ASTExprNode pointer storing the adress of the child node attached to this node
         * @return
         * An ASTExprNode pointer storing the address of the child node attached to this node
         */
        ASTExprNode* getExpr();
        /**
         * This is the implementation of the virtual inherited function
         * @param v
         * Stores the address of the visitor
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTPRINTSTATEMENTNODE_H
