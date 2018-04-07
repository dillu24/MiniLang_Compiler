//
// Created by Dylan Galea on 04/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTEXPRNODE_H

#include "ASTNode.h"
namespace AST {
    class ASTExprNode: public ASTNode{
    private:
    public:
        void accept(Visitor *v) override = 0;
    };
}


#endif //COMPILERSASSIGNMENT_ASTEXPRNODE_H
