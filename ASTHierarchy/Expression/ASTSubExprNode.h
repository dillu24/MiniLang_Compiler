//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTSUBEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTSUBEXPRNODE_H

#include "../ASTExprNode.h"

namespace AST{
    class ASTSubExprNode:public ASTExprNode {
    private:
        ASTExprNode* expression;
    public:
        explicit ASTSubExprNode(ASTExprNode* exp);
        ~ASTSubExprNode();
        void setSubExpr(ASTExprNode* expr);
        ASTExprNode* getSubExpr();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTSUBEXPRNODE_H
