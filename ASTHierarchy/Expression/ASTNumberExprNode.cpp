//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTNumberExprNode.h"
#include "../../Visitors/Visitor.h"

AST::ASTNumberExprNode::ASTNumberExprNode(double val) {
    value=val;
    this->expressionType = NUMBER_EXP; //give appropiate type
}

AST::ASTNumberExprNode::~ASTNumberExprNode() = default;

void AST::ASTNumberExprNode::setValue(double value) {
    this->value=value;
}

double AST::ASTNumberExprNode::getValue() {
    return value;
}

void AST::ASTNumberExprNode::accept(Visitor *v) {
    v->visit(this); //call the visitor's visit implementation to know what to do whenever a visitor visit this node.
}
