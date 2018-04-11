//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTIfStatementNode.h"
#include "../../Visitors/Visitor.h"

ASTIfStatementNode::ASTIfStatementNode(ASTExprNode *expr, ASTBlockStatementNode *tBlock, ASTBlockStatementNode *eBlock) {
    expression = &*expr;
    trueBlock = &* tBlock;
    elseBlock = &* eBlock;
    this->statementType = IF_STMT; //give the required type
}

ASTIfStatementNode::~ASTIfStatementNode() {
    delete(elseBlock,expression,trueBlock);
}

void ASTIfStatementNode::setExpression(ASTExprNode *expr) {
    expression = &* expr;
}

void ASTIfStatementNode::setTrueBlock(ASTBlockStatementNode *tBlock) {
    trueBlock = &*tBlock;
}

void ASTIfStatementNode::setElseBlock(ASTBlockStatementNode *elseBlock) {
    elseBlock = &* elseBlock;
}

ASTExprNode *ASTIfStatementNode::getExpression() {
    return expression;
}

ASTBlockStatementNode *ASTIfStatementNode::getTrueBlock() {
    return trueBlock;
}

ASTBlockStatementNode *ASTIfStatementNode::getElseBlock() {
    return elseBlock;
}

void ASTIfStatementNode::accept(Visitor *v) {
    v->visit(this); //call the visitor's visit implementation to know what to do whenever a visitor visit this node.
}
