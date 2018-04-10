//
// Created by Dylan Galea on 04/04/2018.
//

/**
 * This class encodes the root of all the nodes , it contains the virtual function which is common in all of the
 * nodes , which is the accept function which will be used by the visitor classes.
 **/

#ifndef COMPILERSASSIGNMENT_ASTNODE_H
#define COMPILERSASSIGNMENT_ASTNODE_H


namespace Visitors{  //In order to avoid circular includes , forward declare the Visitor class
    class Visitor;
}
using namespace Visitors;

namespace AST{
    class ASTNode {
    public:
        /**
         * The virtual method that will accept a visitor when it visits some AST node , this must be implemented by
         * all AST nodes.
         * @param v
         * A pointer storing the address of the visitor to visit the AST node.
         */
        virtual void accept(Visitor *v )=0;
    };
}


#endif //COMPILERSASSIGNMENT_ASTNODE_H
