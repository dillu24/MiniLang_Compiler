//
// Created by Dylan Galea on 06/04/2018.
//

#include <minwindef.h>

#include <utility>
#include "ASTVarDeclStatementNode.h"
#include "../../Visitors/Visitor.h"

ASTVarDeclStatementNode::ASTVarDeclStatementNode(string identifier, Type type, ASTExprNode *expr) {
    this->identifier = std::move(identifier);
    this->type = type;
    this->expression = &*expr;
}

ASTVarDeclStatementNode::~ASTVarDeclStatementNode() {
    delete expression;
}

void ASTVarDeclStatementNode::setIdentifier(string ident) {
    identifier = ident;
}

void ASTVarDeclStatementNode::setType(Type type) {
    this->type = type;
}

void ASTVarDeclStatementNode::setExpr(ASTExprNode *expr) {
    expression = &*expr;
}

string ASTVarDeclStatementNode::getIdentifier() {
    return identifier;
}

Type ASTVarDeclStatementNode::getType() {
    return type;
}

ASTExprNode *ASTVarDeclStatementNode::getExpr() {
    return expression;
}

void ASTVarDeclStatementNode::accept(Visitor *v) {
    v->visit(this);
}
