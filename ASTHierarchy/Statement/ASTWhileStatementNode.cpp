//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTWhileStatementNode.h"
#include "../../Visitors/Visitor.h"

ASTWhileStatementNode::ASTWhileStatementNode(ASTExprNode *expr, ASTBlockStatementNode *block) {
    expression = &*expr;
    this->block = &*block;
    this->statementType = WHILE_STMT; //give required type
}

ASTWhileStatementNode::~ASTWhileStatementNode() {
    delete(expression,block);
}

void ASTWhileStatementNode::setExpression(ASTExprNode *expr) {
    expression = &*expr;
}

void ASTWhileStatementNode::setBlock(ASTBlockStatementNode *block) {
    this->block = &*block;
}

ASTExprNode *ASTWhileStatementNode::getExpression() {
    return expression;
}

ASTBlockStatementNode *ASTWhileStatementNode::getBlock() {
    return block;
}

void ASTWhileStatementNode::accept(Visitor *v) {
    v->visit(this);//call the visitor's visit implementation to know what to do whenever a visitor visit this node.
}
