//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTPRINTSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTPRINTSTATEMENTNODE_H

#include "../ASTExprNode.h"
#include "../ASTStatementNode.h"

namespace AST{
    class ASTPrintStatementNode:public ASTStatementNode {
    private:
        ASTExprNode *expression;
    public:
        explicit ASTPrintStatementNode(ASTExprNode* expr);
        ~ASTPrintStatementNode();
        void setExpr(ASTExprNode* expr);
        ASTExprNode* getExpr();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTPRINTSTATEMENTNODE_H
