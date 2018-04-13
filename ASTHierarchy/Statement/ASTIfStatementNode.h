//
// Created by Dylan Galea on 06/04/2018.
//

/**
 * This class is used to encode the if statement node , which will be created whenever the parser matches successfully
 * the production rule related to the if statement. This is a concrete child class of ASTStatementNode , thus it contains
 * the getter,setter,statementType and the virtual accept method . This class also has 3 nodes attached as children , one
 * which stores the predicate , the other which stores the statements that make up the truth of the predicate and the other
 * which stores the statements related to the else block.
 */

#ifndef COMPILERSASSIGNMENT_ASTIFSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTIFSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "ASTBlockStatementNode.h"

namespace AST{
    class ASTIfStatementNode:public ASTStatementNode {
    private:
        ASTExprNode *expression; //This stores the address of the child node expression that must be matches for the if statement to be true
        ASTBlockStatementNode *trueBlock; //stores the address of the child node expression storing the statements that make up the truth block
        ASTBlockStatementNode *elseBlock; // stores the address of the child node expression storing the statements that make
                                          // up the else block
    public:
        /**
         * The constructor used to create a new ASTIfStatementNode storing the values in @param expr,tBlock,eBlock in
         * this->expression,trueBlock,elseBlock
         * @param expr
         * Stores the address of the predicate to be assigned to this->expression
         * @param tBlock
         * Stores the address of the truth block to be assigned to this->trueBlock
         * @param eBlock
         * Stores the address of the else block to be assigned to this->elseBlock
         */
        ASTIfStatementNode(ASTExprNode *expr,ASTBlockStatementNode *tBlock,ASTBlockStatementNode* eBlock);
        /**
         * The destructor used to delete data related to ASTIfStatementNode from the heap
         */
        ~ASTIfStatementNode();
        /**
         * The setter method used to assign values to the private variable this->expression
         * @param expr
         * Stores an address to the expression that will be attached as a child to the ASTIfStatementNode
         */
        void setExpression(ASTExprNode* expr);
        /**
         * The setter method used to assign values to the private variable this->trueBlock
         * @param tBlock
         * Stores the address of the trueBlock that will be attached as child to the ASTIfStatementNode
         */
        void setTrueBlock(ASTBlockStatementNode* tBlock);
        /**
         * The setter method used to assign values to the private variable this->elseBlock
         * @param elseBlock
         * Stores the address of the elseBlock that will be attached as child to the ASTIfStatementNode
         */
        void setElseBlock(ASTBlockStatementNode* elseBlock);
        /**
         * A method used to get the pointer this->expression
         * @return
         * An ASTExprNode pointer storing the address of the child expression node attached to ASTIfStatementNode
         */
        ASTExprNode* getExpression();
        /**
         * A method used to get the pointer this->trueBlock
         * @return
         * An ASTBlockStatementNode pointer storing the address of the child true block attached to ASTIfStatementNode
         */
        ASTBlockStatementNode* getTrueBlock();
        /**
         * A method used to get the pointer this->elseBlock
         * @return
         * An ASTBlockStatementNode pointer storing the address of the child else block attached to ASTIfStatementNode
         */
        ASTBlockStatementNode* getElseBlock();
        /**
         * The implementation of the inherited virtual method from the parents
         * @param v
         * Stores the address of the visitor that will visit this node
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTIFSTATEMENTNODE_H
