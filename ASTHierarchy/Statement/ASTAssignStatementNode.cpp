//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTAssignStatementNode.h"

#include <utility>
#include "../../Visitors/Visitor.h"

ASTAssignStatementNode::ASTAssignStatementNode(string ident, ASTExprNode *expr) {
    identifier = std::move(ident);
    expression = &*expr;
}

ASTAssignStatementNode::~ASTAssignStatementNode() {
    delete expression;
}

void ASTAssignStatementNode::setIdentifier(string identifier) {
    this->identifier = std::move(identifier);
}

void ASTAssignStatementNode::setExpression(ASTExprNode *expr) {
    expression = expr;
}

ASTExprNode *ASTAssignStatementNode::getExpression() {
    return expression;
}

string ASTAssignStatementNode::getIdentifier() {
    return identifier;
}

void ASTAssignStatementNode::accept(Visitor *v) {
    v->visit(this);
}
