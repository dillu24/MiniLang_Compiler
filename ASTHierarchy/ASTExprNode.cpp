//
// Created by Dylan Galea on 11/04/2018.
//
#include "ASTExprNode.h"

AST::ASTExprNode::ExpressionType AST::ASTExprNode::getExpressionType() {
    return expressionType;
}

void AST::ASTExprNode::setExpressionType(ExpressionType expressionType) {
    this->expressionType = expressionType;
}

