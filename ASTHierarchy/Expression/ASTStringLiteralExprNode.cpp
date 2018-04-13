//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTStringLiteralExprNode.h"

#include <utility>
#include "../../Visitors/Visitor.h"

ASTStringLiteralExprNode::ASTStringLiteralExprNode(string sentence) {
    this->sentence= std::move(sentence);
    this->expressionType = STRING_LITERAL_EXP; //give required type
}

ASTStringLiteralExprNode::~ASTStringLiteralExprNode() = default;

void ASTStringLiteralExprNode::setValue(string sentence) {
    this->sentence = std::move(sentence);
}

string ASTStringLiteralExprNode::getValue() {
    return sentence;
}

void ASTStringLiteralExprNode::accept(Visitor *v) {
    v->visit(this); //call the visitor's visit implementation to know what to do whenever a visitor visit this node.
}

