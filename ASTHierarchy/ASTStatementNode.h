//
// Created by Dylan Galea on 04/04/2018.
//

/**
 * This class is a virtual class which is a child of the class ASTNode , however the parent of all Statement nodes
 * according to the grammar given in the specification sheet. As mentioned in the comments for the ASTExpression node
 * class , this class is no different from the ASTNode class , however this branch was needed in order to differ to the
 * parser implementation whenever an expression is parsed ,or whenever a statement is parsed since these are treated
 * differently . This virtual class also contains the common elements amongst all statements which is the accept(Visitor)
 * method.
 **/

#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H

#include "ASTNode.h"

using namespace AST;
namespace AST{
    class ASTStatementNode : public ASTNode {
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


#endif //COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H
