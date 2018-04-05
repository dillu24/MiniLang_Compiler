//
// Created by Dylan Galea on 04/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTNODE_H
#define COMPILERSASSIGNMENT_ASTNODE_H

#include "../Visitors/Visitor.h"
using namespace Visitors;

namespace ASTHierarchy{
    class ASTNode {
    public:
        virtual void accept(Visitor *v ) =0;
    };
}


#endif //COMPILERSASSIGNMENT_ASTNODE_H
