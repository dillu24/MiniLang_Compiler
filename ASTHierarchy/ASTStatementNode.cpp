//
// Created by Dylan Galea on 11/04/2018.
//

#include "ASTStatementNode.h"
using namespace AST;

void ASTStatementNode::setStatementType(ASTStatementNode::StatementType type) {
    this->statementType = type;
}

ASTStatementNode::StatementType ASTStatementNode::getStatementType() {
    return statementType;
}
