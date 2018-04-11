//
// Created by Dylan Galea on 06/04/2018.
//

#include <minwindef.h>

#include <utility>
#include "ASTFuncDeclStatementNode.h"
#include "../../Visitors/Visitor.h"

ASTFuncDeclStatementNode::ASTFuncDeclStatementNode(AST::ASTIdentifierExprNode* identifier, FormalParams *fp, Type type,
                                                   ASTBlockStatementNode *block) {
    this->identifier = &*identifier;
    this->fp = &*fp;
    this->type = type;
    this->block =&*block;
    this->statementType = FUNC_DECL_STMT;
}

ASTFuncDeclStatementNode::~ASTFuncDeclStatementNode() {
    delete (fp,block,identifier);
}

void ASTFuncDeclStatementNode::setIdentifier(AST::ASTIdentifierExprNode* ident) {
    this->identifier=&*identifier;
}

void ASTFuncDeclStatementNode::setFormalParams(FormalParams *fp) {
    this->fp = &*fp;
}

void ASTFuncDeclStatementNode::setType(Type type) {
    this->type = type;
}

void ASTFuncDeclStatementNode::setBlock(ASTBlockStatementNode *block) {
    this->block = &*block;
}

AST::ASTIdentifierExprNode* ASTFuncDeclStatementNode::getIdentifier() {
    return identifier;
}

FormalParams *ASTFuncDeclStatementNode::getFormalParams() {
    return fp;
}

Type ASTFuncDeclStatementNode::getType() {
    return type;
}

ASTBlockStatementNode *ASTFuncDeclStatementNode::getBlock() {
    return block;
}

void ASTFuncDeclStatementNode::accept(Visitor *v) {
    v->visit(this);
}
