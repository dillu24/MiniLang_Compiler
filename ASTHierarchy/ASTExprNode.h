//
// Created by Dylan Galea on 04/04/2018.
//
/**
 * This class is used to encode the expression nodes , this is no different from the ASTNode class since there were
 * no more common fields and behaviours that could be found within the expressions . However a distinction had to be
 * made since the Parser treats expressions and statements differently. This class also inherits from the ASTNode class
 * since an AST expression is indeed an AST node. This class is also a virtual class since it has no specific implementation
 * for the accept function , thus more concrete classes need to be defined.
 **/

#ifndef COMPILERSASSIGNMENT_ASTEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTEXPRNODE_H

#include "ASTNode.h"
namespace AST {
    class ASTExprNode: public ASTNode{
    private:
    public:
        /**
         * The accept method inherited from class ASTNode , here it is not implemented since ASTExprNode is a virtual
         * class
         * @param v
         * A pointer to a visitor that is going to visit the node.
         */
        void accept(Visitor *v) override = 0;
    };
}


#endif //COMPILERSASSIGNMENT_ASTEXPRNODE_H
