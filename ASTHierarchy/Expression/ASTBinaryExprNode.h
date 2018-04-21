//
// Created by Dylan Galea on 06/04/2018.
//
/**
 * This is the ASTBinaryExprNode class and is used to encode an expression that has an operator with operands on
 * the left hand side and on the right hand side appended to it. Note that in this implementation the Operators class
 * is not a node ,but a type in order to store the operator. Thus the children of this node are the expression on the
 * left hand side and the expression on the right hand side. This is a concrete class and is a child of the ASTExprNode,
 * so it must implement the accept method
 */
#ifndef COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H

#include "../ASTExprNode.h"
#include "../Operators.h"

namespace AST {
    class ASTBinaryExprNode:public ASTExprNode {
    private:
        ASTExprNode *Lhs; //Stores the address of an ASTExprNode that contains the Left hand side of the expression
        ASTExprNode *Rhs; //Stores the address of an ASTExprNode that contains the Right hand side of the expression.
        Operators op; //Stores the operator that binds the expression.
    public:
        /**
         * The constructor used to initialize all attributes of the class
         * @param left
         * Stores a pointer to the Left hand side of the expression that will be assigned to the variable "Lhs"
         * @param right
         * Stores a pointer to the Right hand side of the expression that will be assigned to the variable "Rhs"
         * @param oper
         * Stores the operator that will be stored in variable "op"
         */
        ASTBinaryExprNode(ASTExprNode *left,ASTExprNode *right,Operators oper);
        /**
         * This destructor is used to delete all attributes of the node that are on the heap
         */
        ~ASTBinaryExprNode();
        /**
         * This setter method is used to give the left hand side a value
         * @param left
         * Stores a pointer to the left hand side of the expression to be assigned to the variable "Lhs"
         */
        void setLhs(ASTExprNode *left);
        /**
         * This setter method is used to give the right hand side a value
         * @param right
         * Stores a pointer to the right hand side of the expression to be assigned to the variable "Rhs"
         */
        void setRhs(ASTExprNode *right);
        /**
         * This setter method is used to give the operator attribute a value
         * @param op
         * Stores the operator of type class Operators whose value is to be stored in the variable "op"
         */
        void setOperator(Operators op);
        /**
         * A getter method used to return the value stored in the variable Lhs , since it is private
         * @return
         * A pointer to an ASTExprNode that stores the address of the left hand side of the expression
         */
        ASTExprNode* getLhs();
        /**
         * A getter method used to return the value stored in the variable Rhs , since it is private
         * @return
         * A pointer to an ASTExprNode that stores the address of the right hand side of the expression.
         */
        ASTExprNode* getRhs();
        /**
         * A getter method used to return the value stored in the variable "op" , since it is private
         * @return
         * The value stored in the variable "op"
         */
        Operators getOperator();
        /**
         * The accept method inherited from the parents must be implemented since the ASTBinaryExprNode class is not
         * a virtual class.
         * @param v
         * Stores the address of the visitor that is visiting the node.
         */
        void accept(Visitor *v) override;

        /**
         * This method is used so that in the visitor classes whenever the operator needs to be printed it can
         * be printed using this function according to the enum name.
         */
        void printOperator();
    };
}


#endif //COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H
