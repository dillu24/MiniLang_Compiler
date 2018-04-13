//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTBinaryExprNode.h"
#include "../../Visitors/Visitor.h"
using namespace AST;

ASTBinaryExprNode::ASTBinaryExprNode(ASTExprNode *left, ASTExprNode *right, Operators oper) { //assign values to fields
    Lhs = &*left;
    Rhs = &*right;
    op = oper;
    this->expressionType = ExpressionType::BINARY_EXP;
}

ASTBinaryExprNode::~ASTBinaryExprNode() { //remove heap data
    delete Lhs;
    delete Rhs;
}

void ASTBinaryExprNode::setLhs(ASTExprNode *left) { //assign required value
    Lhs = &*left;
}

void ASTBinaryExprNode::setRhs(ASTExprNode *right) {//assign required value
    Rhs = &*right;
}

ASTExprNode *ASTBinaryExprNode::getLhs() { //get required value
    return Lhs;
}

ASTExprNode *ASTBinaryExprNode::getRhs() { //get required value
    return Rhs;
}

void AST::ASTBinaryExprNode::accept(Visitor *v) {
    v->visit(this); //visit the node according to the visitor's implementation
}

void ASTBinaryExprNode::setOperator(Operators op) { //set the required value
    this->op = op;
}

Operators ASTBinaryExprNode::getOperator() { //get the required value
    return op;
}
