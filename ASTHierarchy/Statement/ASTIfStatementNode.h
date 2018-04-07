//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTIFSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTIFSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "ASTBlockStatementNode.h"

namespace AST{
    class ASTIfStatementNode:public ASTStatementNode {
    private:
        ASTExprNode *expression;
        ASTBlockStatementNode *trueBlock;
        ASTBlockStatementNode *elseBlock;
    public:
        ASTIfStatementNode(ASTExprNode *expr,ASTBlockStatementNode *tBlock,ASTBlockStatementNode* eBlock);
        ~ASTIfStatementNode();
        void setExpression(ASTExprNode* expr);
        void setTrueBlock(ASTBlockStatementNode* tBlock);
        void setElseBlock(ASTBlockStatementNode* elseBlock);
        ASTExprNode* getExpression();
        ASTBlockStatementNode* getTrueBlock();
        ASTBlockStatementNode* getElseBlock();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTIFSTATEMENTNODE_H
