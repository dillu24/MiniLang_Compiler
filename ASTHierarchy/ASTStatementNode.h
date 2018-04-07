//
// Created by Dylan Galea on 04/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H

#include "ASTNode.h"

using namespace AST;
namespace AST{
    class ASTStatementNode : public ASTNode {
    public:
        void accept(Visitor *v) override = 0;
    };
}


#endif //COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H
