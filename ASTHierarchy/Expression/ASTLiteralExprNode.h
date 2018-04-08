//
// Created by Dylan Galea on 08/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTLITERALEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTLITERALEXPRNODE_H

#include "../ASTExprNode.h"

namespace AST{
    class ASTLiteralExprNode:public ASTExprNode {
    public:
        void accept(Visitor *v) override =0;
    };
}

#endif //COMPILERSASSIGNMENT_ASTLITERALEXPRNODE_H
