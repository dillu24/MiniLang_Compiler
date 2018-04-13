//
// Created by Dylan Galea on 07/04/2018.
//

/**
 * This class encodes the node whenever a boolean expression is identified in the program , this class is a child of
 * the virtual class LiteralExprNode . Since it is a concrete class it has to implement the accept method inherited
 * from previous classes . It also contains the getters and setters for the expressionType variable.
 */

#ifndef COMPILERSASSIGNMENT_ASTBOOLEANLITERALEXPRESSIONNODE_H
#define COMPILERSASSIGNMENT_ASTBOOLEANLITERALEXPRESSIONNODE_H

#include "../ASTExprNode.h"
#include "ASTLiteralExprNode.h"

namespace AST{
    class ASTBooleanLiteralExpressionNode:public ASTLiteralExprNode {
    private:
        bool value; //stores the literal value in the expression
    public:
        /**
         * The constructor used to initialize a new ASTBooleanLiteralExpressionNode with a boolean value
         * @param value
         * Stores the value that will be assigned to the variable "value"
         */
        explicit ASTBooleanLiteralExpressionNode(bool value);
        /**
         * The setter method used to give the private variable "value" a boolean value.
         * @param value
         * The value that will be assigned to the variable "value"
         */
        void setValue(bool value);
        /**
         * The getter method used to get the value stored in the private variable "value"
         * @return
         * The value stored in "value"
         */
        bool getValue();
        /**
         * The implementation of the virtual method inherited from previous classes.
         * @param v
         * A pointer to a visitor that is vising the node.
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTBOOLEANLITERALEXPRESSIONNODE_H
