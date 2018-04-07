//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTBooleanLiteralExpressionNode.h"
#include "../../Visitors/Visitor.h"

AST::ASTBooleanLiteralExpressionNode::ASTBooleanLiteralExpressionNode(bool value) {
    this->value=value;
}

void AST::ASTBooleanLiteralExpressionNode::setValue(bool value) {
    this->value=value;
}

bool AST::ASTBooleanLiteralExpressionNode::getValue() {
    return value;
}

void AST::ASTBooleanLiteralExpressionNode::accept(Visitor *v) {
    v->visit(this);
}
