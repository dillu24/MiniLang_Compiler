//
// Created by Dylan Galea on 08/04/2018.
//

/**
 * This is a virtual class used to distinguish the LiteralNodes from the rest of the Expression nodes , thus creating
 * a better hierarchy . This was done in order to make a more concise hierarchy , and in the parser , a parseLiteral
 * method could be done , thus making the parsing method more concise.
 */
#ifndef COMPILERSASSIGNMENT_ASTLITERALEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTLITERALEXPRNODE_H

#include "../ASTExprNode.h"

namespace AST{
    class ASTLiteralExprNode:public ASTExprNode {
    public:
        /**
         * The virtual method inherited from the ASTExprNode is still virtual , thus must be implemented in the concrete
         * classes.
         * @param v
         * Stores a pointer to a visitor that is going to visit the node.
         */
        void accept(Visitor *v) override =0;
    };
}

#endif //COMPILERSASSIGNMENT_ASTLITERALEXPRNODE_H
