//
// Created by Dylan Galea on 06/04/2018.
//
/**
 * This class is used to encodes the node that is created whenever the parser matches the production rule related to
 * while statements . This class is a child of the ASTStatementNode , thus containing all the methods and variables
 * related to the inherited enum StatementType along with the implementation of the virtual accept method. This node also
 * contains 2 nodes as children , one is the expression that must be matches in order to loop , and the other child is
 * the block statement to be run if the predicate is met. Since these 2 branches were declared as private , setters
 * and getters had to be designed.
 */

#ifndef COMPILERSASSIGNMENT_ASTWHILESTATEMENTBLOCK_H
#define COMPILERSASSIGNMENT_ASTWHILESTATEMENTBLOCK_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "ASTBlockStatementNode.h"

namespace AST{
    class ASTWhileStatementNode:public ASTStatementNode {
    private:
        ASTExprNode* expression; //stores the address of the predicate attached as child to ASTWhileStatementNode
        ASTBlockStatementNode* block; //stores the address of the block attached as child to ASTWhileStatementNode.
    public:
        /**
         * The constructor used to create a new ASTWhileStatement node storing the values of @param expr,block in
         * this->expression , this->block
         * @param expr
         * Contains the address of the expression node to be attached as child to ASTWhileStatementNode
         * @param block
         * Contains the address of the block node to be attached as child to ASTWhileStatementNode.
         */
        ASTWhileStatementNode(ASTExprNode* expr,ASTBlockStatementNode* block);
        /**
         * The destructor used to delete the data related to the ASTWhileStatementNode from the heap
         */
        ~ASTWhileStatementNode();
        /**
         * This setter is used to give a value to this->expression
         * @param expr
         * Stores the address of the expression to be assigned to this->expression
         */
        void setExpression(ASTExprNode* expr);
        /**
         * This setter is used to give a value to this->block
         * @param block
         * Stores the address of the block to be assigned to this->block
         */
        void setBlock(ASTBlockStatementNode* block);
        /**
         * This method is used to get the private pointer this->expression
         * @return
         * The pointer this->expression
         */
        ASTExprNode* getExpression();
        /**
         * This method is used to get the private pointer this->block
         * @return
         * The pointer this->block
         */
        ASTBlockStatementNode* getBlock();
        /**
         * This is the implementation of the virtual method inherited from parent classes
         * @param v
         * Stores the address of visitor that is visiting this node.
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTWHILESTATEMENTBLOCK_H
