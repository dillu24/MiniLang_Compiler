//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTStringLiteralExprNode.h"

#include <utility>
#include "../../Visitors/Visitor.h"

AST::ASTStringLiteralExprNode::ASTStringLiteralExprNode(string sentence) {
    this->sentence= std::move(sentence);
}

void AST::ASTStringLiteralExprNode::setSentence(string sentence) {
    this->sentence= std::move(sentence);
}

string AST::ASTStringLiteralExprNode::getSentence() {
    return sentence;
}

void AST::ASTStringLiteralExprNode::accept(Visitor *v) {
    v->visit(this);
}
