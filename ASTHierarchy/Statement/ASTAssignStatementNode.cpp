//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTAssignStatementNode.h"

#include <utility>
#include "../../Visitors/Visitor.h"

ASTAssignStatementNode::ASTAssignStatementNode(ASTIdentifierExprNode* ident, ASTExprNode *expr) {
    identifier = &*ident;
    expression = &*expr;
    this->statementType = ASSIGN_STMT; //give required type
}

ASTAssignStatementNode::~ASTAssignStatementNode() {
    delete(identifier,expression);
}

void ASTAssignStatementNode::setIdentifier(ASTIdentifierExprNode* identifier) {
    this->identifier = &*identifier;
}

void ASTAssignStatementNode::setExpression(ASTExprNode *expr) {
    expression = &*expr;
}

ASTExprNode *ASTAssignStatementNode::getExpression() {
    return expression;
}

ASTIdentifierExprNode* ASTAssignStatementNode::getIdentifier() {
    return identifier;
}

void ASTAssignStatementNode::accept(Visitor *v) {
    v->visit(this); //call the visitor's visit implementation to know what to do whenever a visitor visit this node.
}
