//
// Created by Dylan Galea on 06/04/2018.
//

#include "ASTBinaryExprNode.h"
#include "../../Visitors/Visitor.h"
using namespace AST;

ASTBinaryExprNode::ASTBinaryExprNode(ASTExprNode *left, ASTExprNode *right, char oper) {
    Lhs = &*left;
    Rhs = &*left;
    op = oper;
}

ASTBinaryExprNode::~ASTBinaryExprNode() {
    delete Lhs;
    delete Rhs;
}

void ASTBinaryExprNode::setLhs(ASTExprNode *left) {
    Lhs = &*left;
}

void ASTBinaryExprNode::setRhs(ASTExprNode *right) {
    Rhs = &*right;
}

ASTExprNode *ASTBinaryExprNode::getLhs() {
    return Lhs;
}

ASTExprNode *ASTBinaryExprNode::getRhs() {
    return Rhs;
}

void AST::ASTBinaryExprNode::accept(Visitor *v) {
    v->visit(this);
}
