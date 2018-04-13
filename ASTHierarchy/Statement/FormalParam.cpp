//
// Created by Dylan Galea on 07/04/2018.
//

#include "FormalParam.h"

AST::FormalParam::FormalParam(AST::ASTIdentifierExprNode *ident, AST::Type type) {
    identifier = &*ident;
    this->type=type;
}

void AST::FormalParam::setIdentifier(AST::ASTIdentifierExprNode *ident) {
    identifier = &*ident;
}

void AST::FormalParam::setType(AST::Type type) {
    this->type = type;
}

AST::ASTIdentifierExprNode* AST::FormalParam::getIdentifier() {
    return identifier;
}

AST::Type AST::FormalParam::getType() {
    return type;
}
