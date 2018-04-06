//
// Created by Dylan Galea on 04/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTNODE_H
#define COMPILERSASSIGNMENT_ASTNODE_H


namespace Visitors{
    class Visitor;
}
using namespace Visitors;
namespace AST{
    class ASTNode {
    public:
        virtual void accept(Visitor *v ) =0;
    };
}


#endif //COMPILERSASSIGNMENT_ASTNODE_H
