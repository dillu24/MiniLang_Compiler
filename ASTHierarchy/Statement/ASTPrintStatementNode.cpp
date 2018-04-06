//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTPrintStatementNode.h"
#include "../../Visitors/Visitor.h"

ASTPrintStatementNode::ASTPrintStatementNode(ASTExprNode *expr) {
    expression = &*expr;
}

ASTPrintStatementNode::~ASTPrintStatementNode() {
    delete expression;
}

void ASTPrintStatementNode::setExpr(ASTExprNode *expr) {
    expression = &*expr;
}

ASTExprNode *ASTPrintStatementNode::getExpr() {
    return expression;
}

void ASTPrintStatementNode::accept(Visitor *v) {
    v->visit(this);
}
