//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTWHILESTATEMENTBLOCK_H
#define COMPILERSASSIGNMENT_ASTWHILESTATEMENTBLOCK_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "ASTBlockStatementNode.h"

namespace AST{
    class ASTWhileStatementNode:public ASTStatementNode {
    private:
        ASTExprNode* expression;
        ASTBlockStatementNode* block;
    public:
        ASTWhileStatementNode(ASTExprNode* expr,ASTBlockStatementNode* block);
        ~ASTWhileStatementNode();
        void setExpression(ASTExprNode* expr);
        void setBlock(ASTBlockStatementNode* block);
        ASTExprNode* getExpression();
        ASTBlockStatementNode* getBlock();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTWHILESTATEMENTBLOCK_H
