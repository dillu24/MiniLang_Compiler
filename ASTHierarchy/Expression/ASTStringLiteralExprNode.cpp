//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTStringLiteralExprNode.h"

#include <utility>
#include "../../Visitors/Visitor.h"

ASTStringLiteralExprNode::ASTStringLiteralExprNode(string sentence) {
    this->sentence= std::move(sentence);
}

ASTStringLiteralExprNode::~ASTStringLiteralExprNode() = default;

void ASTStringLiteralExprNode::setValue(string sentence) {
    this->sentence = std::move(sentence);
}

string ASTStringLiteralExprNode::getValue() {
    return sentence;
}

void ASTStringLiteralExprNode::accept(Visitor *v) {
    v->visit(this);
}

