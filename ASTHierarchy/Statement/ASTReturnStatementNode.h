//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTRETURNSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTRETURNSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"

namespace AST{
    class ASTReturnStatementNode:public ASTStatementNode {
    private:
        ASTExprNode* expression;
    public:
        explicit ASTReturnStatementNode(ASTExprNode* expr);
        ~ASTReturnStatementNode();
        void setExpression(ASTExprNode* expr);
        ASTExprNode* getExpression();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTRETURNSTATEMENTNODE_H
