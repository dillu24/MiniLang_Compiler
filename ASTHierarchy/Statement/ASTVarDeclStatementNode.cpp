//
// Created by Dylan Galea on 06/04/2018.
//

#include <minwindef.h>

#include <utility>
#include <iostream>
#include "ASTVarDeclStatementNode.h"
#include "../../Visitors/Visitor.h"


ASTVarDeclStatementNode::ASTVarDeclStatementNode() = default;

ASTVarDeclStatementNode::ASTVarDeclStatementNode(AST::ASTIdentifierExprNode *identifier, Type type, ASTExprNode *expr) {
    this->identifier = &*identifier;
    this->type = type;
    this->expression = &*expr;
    this->statementType = VAR_DECL_STMT; //give the required type
}

ASTVarDeclStatementNode::~ASTVarDeclStatementNode() {
    delete (expression,identifier);
}

void ASTVarDeclStatementNode::setIdentifier(AST::ASTIdentifierExprNode* ident) {
    identifier = &*ident;
}

void ASTVarDeclStatementNode::setType(Type type) {
    this->type = type;
}

void ASTVarDeclStatementNode::setExpr(ASTExprNode *expr) {
    expression = &*expr;
}

AST::ASTIdentifierExprNode* ASTVarDeclStatementNode::getIdentifier() {
    return identifier;
}

Type ASTVarDeclStatementNode::getType() {
    return type;
}

ASTExprNode *ASTVarDeclStatementNode::getExpr() {
    return expression;
}

void ASTVarDeclStatementNode::accept(Visitor *v) {
    v->visit(this); //call the visitor's visit implementation to know what to do whenever a visitor visit this node.
}

void ASTVarDeclStatementNode::printType() {
    switch(type){
        case Type::REAL:
            cout<<"real";
            break;
        case Type::INT:
            cout<<"int";
            break;
        case Type::BOOL:
            cout<<"bool";
            break;
        case Type::STRING:
            cout<<"string";
            break;
    }
}
