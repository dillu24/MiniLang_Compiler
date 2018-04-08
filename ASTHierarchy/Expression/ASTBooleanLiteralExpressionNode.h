//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTBOOLEANLITERALEXPRESSIONNODE_H
#define COMPILERSASSIGNMENT_ASTBOOLEANLITERALEXPRESSIONNODE_H

#include "../ASTExprNode.h"
#include "ASTLiteralExprNode.h"

namespace AST{
    class ASTBooleanLiteralExpressionNode:public ASTLiteralExprNode {
    private:
        bool value;
    public:
        explicit ASTBooleanLiteralExpressionNode(bool value);
        void setValue(bool value);
        bool getValue();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTBOOLEANLITERALEXPRESSIONNODE_H
