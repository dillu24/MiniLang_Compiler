//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTIdentifierExprNode.h"

#include <utility>
#include "../../Visitors/Visitor.h"

ASTIdentifierExprNode::ASTIdentifierExprNode(){
    this->expressionType = IDENTIFIER_EXP;
}

AST::ASTIdentifierExprNode::ASTIdentifierExprNode(string identifier) {
    identifierName = std::move(identifier);
    this->expressionType = IDENTIFIER_EXP;
}

void AST::ASTIdentifierExprNode::setIdentifierName(string value) {
    identifierName= std::move(value);
}

string AST::ASTIdentifierExprNode::getIdentifierName() {
    return identifierName;
}

void AST::ASTIdentifierExprNode::accept(Visitor *v) {
    v->visit(this);
}
