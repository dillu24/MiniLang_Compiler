//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTReturnStatementNode.h"
#include "../../Visitors/Visitor.h"


ASTReturnStatementNode::ASTReturnStatementNode(ASTExprNode *expr) {
    expression = &*expr;
}

ASTReturnStatementNode::~ASTReturnStatementNode() {
    delete expression;
}

void ASTReturnStatementNode::setExpression(ASTExprNode *expr) {
    expression =&*expr;
}

ASTExprNode *ASTReturnStatementNode::getExpression() {
    return expression;
}

void ASTReturnStatementNode::accept(Visitor *v) {
    v->visit(this);
}
