//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTUNARYEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTUNARYEXPRNODE_H

#include "../NegationOperator.h"
#include "../ASTExprNode.h"

namespace AST{
    class ASTUnaryExprNode:public ASTExprNode {
    private:
        NegationOperator op;
        ASTExprNode* expression;
    public:
        ASTUnaryExprNode(NegationOperator op,ASTExprNode* expression);
        ~ASTUnaryExprNode();
        void setOp(NegationOperator op);
        void setExpression(ASTExprNode* expression);
        NegationOperator getOp();
        ASTExprNode* getExpression();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTUNARYEXPRNODE_H
