//
// Created by Dylan Galea on 13/04/2018.
//

#include <iostream>
#include "XMLGenerator.h"

Visitors::XMLGenerator::XMLGenerator() {
    indentationLevel = "";
}

void Visitors::XMLGenerator::visitTree(vector<ASTStatementNode *> *tree) {
    cout<<"<AbstractSyntaxTree>"<<endl;
    TabIn();
    for (auto &i : *tree) {
        i->accept(this);
    }
    TabOut();
    cout<<"</AbstractSyntaxTree>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTAssignStatementNode *node) {

}

void Visitors::XMLGenerator::visit(ASTBlockStatementNode *node) {

}

void Visitors::XMLGenerator::visit(ASTIfStatementNode *node) {

}

void Visitors::XMLGenerator::visit(ASTPrintStatementNode *node) {
    cout<<indentationLevel<<"<print>"<<endl;
    TabIn();
    node->getExpr()->accept(this);
    TabOut();
    cout<<indentationLevel<<"</print>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTVarDeclStatementNode *node) {

}

void Visitors::XMLGenerator::visit(ASTWhileStatementNode *node) {

}

void Visitors::XMLGenerator::visit(ASTReturnStatementNode *node) {
    cout<<indentationLevel<<"<return>"<<endl;
    TabIn();
    node->getExpression()->accept(this);
    TabOut();
    cout<<indentationLevel<<"</return>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTFuncDeclStatementNode *node) {

}

void Visitors::XMLGenerator::visit(ASTBinaryExprNode *node) {
    cout<<indentationLevel<<"<BinaryExp Op=\"";
    node->printOperator();
    cout<<"\">"<<endl;
    TabIn();
    node->getLhs()->accept(this);
    node->getRhs()->accept(this);
    TabOut();
    cout<<indentationLevel<<"</BinaryExp>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTNumberExprNode *node) {
    cout<<indentationLevel<<"<Number>"<<node->getValue()<<"</Number>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTBooleanLiteralExpressionNode *node) {
    cout<<indentationLevel<<"<Bool>"<<node->getValue()<<"</Bool>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTStringLiteralExprNode *node) {
    cout<<indentationLevel<<"<StringLiteral>"<<node->getValue()<<"</StringLiteral>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTIdentifierExprNode *node) {
    cout<<indentationLevel<<"<Identifier>"<<node->getIdentifierName()<<"</Identifier>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTSubExprNode *node) {
    cout<<indentationLevel<<"<SubExp>"<<endl;
    TabIn();
    node->getSubExpr()->accept(this);
    TabOut();
    cout<<indentationLevel<<"</SubExp>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTUnaryExprNode *node) {
    cout<<indentationLevel<<"<UnaryExp Op=\"";
    node->printNegOp();
    cout<<"\">"<<endl;
    TabIn();
    node->getExpression()->accept(this);
    TabOut();
    cout<<indentationLevel<<"</UnaryExp>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTFnCallExprNode *node) {
}

void Visitors::XMLGenerator::TabIn() {
    indentationLevel.push_back('\t');
}

void Visitors::XMLGenerator::TabOut() {
    indentationLevel.pop_back();
}

