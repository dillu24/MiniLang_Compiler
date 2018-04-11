//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTBlockStatementNode.h"
#include "../../Visitors/Visitor.h"

ASTBlockStatementNode::ASTBlockStatementNode(vector<ASTStatementNode *>* statements) {
    this->statements = &*statements;
    this->statementType = BLOCK_STMT;
}

ASTBlockStatementNode::~ASTBlockStatementNode() {
    for (auto &statement : *statements) {
        delete statement;
    }
    delete statements;
}

void ASTBlockStatementNode::addStatement(ASTStatementNode *statement) {
    statements->push_back(statement);
}

vector<ASTStatementNode *>* ASTBlockStatementNode::getStatements() {
    return statements;
}

void ASTBlockStatementNode::removeStatement(int index) {
    statements->erase(statements->begin()+index);
}

void ASTBlockStatementNode::accept(Visitor *v) {
    v->visit(this);
}
