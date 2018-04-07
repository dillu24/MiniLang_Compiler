//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTUnaryExprNode.h"
#include "../../Visitors/Visitor.h"

ASTUnaryExprNode::ASTUnaryExprNode(NegationOperator op, ASTExprNode *expression) {
    this->op = op;
    this->expression = &* expression;
}

ASTUnaryExprNode::~ASTUnaryExprNode() {
    delete expression;
}

void ASTUnaryExprNode::setOp(NegationOperator op) {
    this->op=op;
}

void ASTUnaryExprNode::setExpression(ASTExprNode *expression) {
    this->expression=&*expression;
}

NegationOperator ASTUnaryExprNode::getOp() {
    return op;
}

ASTExprNode *ASTUnaryExprNode::getExpression() {
    return expression;
}

void ASTUnaryExprNode::accept(Visitor *v) {
    v->visit(this);
}
