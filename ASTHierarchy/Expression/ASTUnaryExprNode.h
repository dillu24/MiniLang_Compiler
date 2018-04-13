//
// Created by Dylan Galea on 07/04/2018.
//

/**
 * This class is used to encode an AST unary expression node , that is created whenever the parser makes sure that
 * all the production rule related to unary expressions is satisfied . This is a concrete child class of ASTExprNode , thus
 * it contains the getter,setter,and expressionType variable related to the enum class ExpressionType and the accept
 * virtual method . An ASTUnaryExpression node must stored the negation operator that caused the node to be created ,
 * which is of type enum NegationOperator , and stores also stores a child ASTExprNode that stores the expression to be
 * negated.
 */

#ifndef COMPILERSASSIGNMENT_ASTUNARYEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTUNARYEXPRNODE_H

#include "../NegationOperator.h"
#include "../ASTExprNode.h"

namespace AST{
    class ASTUnaryExprNode:public ASTExprNode {
    private:
        NegationOperator op; //stores the operator that caused the node to be created
        ASTExprNode* expression; // Stores the address of the ASTExprNode that is attached as a child to the unaryExprNode
    public:
        /**
         * The constructor used to create a new ASTUnaryExprNode , storing @param op's value in this->op and @param's
         * expression value in this->expression
         * @param op
         * Stores the operator that will be stored in this->op
         * @param expression
         * Stores the expression that will be assigned to this->expression
         */
        ASTUnaryExprNode(NegationOperator op,ASTExprNode* expression);
        /**
         * The destructor used to delete all memory from the heap related to the class ASTUnaryExprNode
         */
        ~ASTUnaryExprNode();
        /**
         * The setter method used to give a value to the private variable this->op
         * @param op
         * Stores the operator value that will be assigned to this->op
         */
        void setOp(NegationOperator op);
        /**
         * The setter method used to give a value to the private variable this->expression
         * @param expression
         * Stores the expression that will be assigned to this->expression
         */
        void setExpression(ASTExprNode* expression);
        /**
         * The getter method used to get the value stored in the private variable this->op
         * @return
         * The operator value stored in this->op of type enum Operators
         */
        NegationOperator getOp();
        /**
         * The getter method used to get the value stored in the private this->expression
         * @return
         * An ASTExprNode* storing the address of the child expression node attached to ASTUnaryExprNode
         */
        ASTExprNode* getExpression();
        /**
         * The implementation of the virtual inherited method
         * @param v
         * Stores the address of the visitor visiting this node.
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTUNARYEXPRNODE_H
