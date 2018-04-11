//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTSubExprNode.h"
#include "../../Visitors/Visitor.h"

AST::ASTSubExprNode::ASTSubExprNode(AST::ASTExprNode *exp) {
    expression =&*exp;
    this->expressionType = SUB_EXP;
}

AST::ASTSubExprNode::~ASTSubExprNode() {
    delete expression;
}

void AST::ASTSubExprNode::setSubExpr(AST::ASTExprNode *expr) {
    expression = &*expr;
}

AST::ASTExprNode *AST::ASTSubExprNode::getSubExpr() {
    return expression;
}

void AST::ASTSubExprNode::accept(Visitor *v) {
    v->visit(this);
}
