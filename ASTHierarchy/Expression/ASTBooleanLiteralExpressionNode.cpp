//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTBooleanLiteralExpressionNode.h"
#include "../../Visitors/Visitor.h"

AST::ASTBooleanLiteralExpressionNode::ASTBooleanLiteralExpressionNode(bool value) { //assign values as required
    this->value=value;
    this->expressionType = ExpressionType::BOOLEAN_LITERAL_EXP; //give type according to node name
}

void AST::ASTBooleanLiteralExpressionNode::setValue(bool value) { // set value to value given in parameters
    this->value=value;
}

bool AST::ASTBooleanLiteralExpressionNode::getValue() { //get the value
    return value;
}

void AST::ASTBooleanLiteralExpressionNode::accept(Visitor *v) { //call the visitor's method when visiting this type of node
    v->visit(this);
}
