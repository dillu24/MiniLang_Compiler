//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTReturnStatementNode.h"
#include "../../Visitors/Visitor.h"


ASTReturnStatementNode::ASTReturnStatementNode(ASTExprNode *expr) {
    expression = &*expr;
    this->statementType = RETURN_STMT; //give the required type
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
    v->visit(this); //call the visitor's visit implementation to know what to do whenever a visitor visit this node.
}
