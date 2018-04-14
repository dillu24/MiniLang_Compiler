//
// Created by Dylan Galea on 14/04/2018.
//

#include <cmath>
#include "SemanticAnalysis.h"

SemanticAnalysis::SemanticAnalysis() {
    ScopedTable = vector<SymbolTable*>();
}

void SemanticAnalysis::visit(ASTAssignStatementNode *node) { //this was done such that reals cannot be typecaster to ints , as secpfied
    node->getIdentifier()->accept(this);
    Type identifierType = typeToBeChecked;
    node->getExpression()->accept(this);
    Type expressionType = typeToBeChecked;
    if(identifierType != expressionType){
        cout<<"The identifier "<<node->getIdentifier()->getIdentifierName()
            <<" does not have the same type as expression"<<endl;
        exit(-1);
    }
}

void SemanticAnalysis::visit(ASTBlockStatementNode *node) {

}

void SemanticAnalysis::visit(ASTIfStatementNode *node) {

}

void SemanticAnalysis::visit(ASTPrintStatementNode *node) {
    node->getExpr()->accept(this);
}

void SemanticAnalysis::visit(ASTVarDeclStatementNode *node) {
    if(ScopedTable.at(ScopedTable.size()-1)->checkIfInSymbolTable(node->getIdentifier()->getIdentifierName()) &&
            ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).
                    getIdentifierType() == TypeBinder::VARIABLE){
        cout<<"A variable with name "<<node->getIdentifier()->getIdentifierName()<<" has already been declared in this scope "<<endl;
        exit(-1);
    }
    node->getExpr()->accept(this);
    if(typeToBeChecked == node->getType()){
        TypeBinder tb = TypeBinder(typeToBeChecked,TypeBinder::IdentifierType::VARIABLE);
        ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),tb);
    }else{
        cout<<"Type of variable "<<node->getIdentifier()->getIdentifierName()<<" does not match with expression"<<endl;
        exit(-1);
    }
}

void SemanticAnalysis::visit(ASTWhileStatementNode *node) {

}

void SemanticAnalysis::visit(ASTReturnStatementNode *node) {
    node->getExpression()->accept(this);
}

void SemanticAnalysis::visit(ASTFuncDeclStatementNode *node) {

}

void SemanticAnalysis::visit(ASTBinaryExprNode *node) { //check binary operators while doing expressions for all sub part of expression

}

void SemanticAnalysis::visit(ASTNumberExprNode *node) {
    double integerPart = 0.0;
    if(modf(node->getValue(),&integerPart)==0.0){
        typeToBeChecked =  Type::INT;
    }else{
        typeToBeChecked = Type::REAL;
    }
}

void SemanticAnalysis::visit(ASTBooleanLiteralExpressionNode *node) {
    typeToBeChecked = Type::BOOL;
}

void SemanticAnalysis::visit(ASTStringLiteralExprNode *node) {
    typeToBeChecked = Type::STRING;
}

void SemanticAnalysis::visit(ASTIdentifierExprNode *node) {
    for(int i=0;i<ScopedTable.size();i++){
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifierName())){
            typeToBeChecked = ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifierName()).getPrimitiveType();
            return;
        }
    }
    cout<<"Variable "<<node->getIdentifierName()<<" was not declared"<<endl;
    exit(-1);
}

void SemanticAnalysis::visit(ASTSubExprNode *node) {
    node->getSubExpr()->accept(this);
}

void SemanticAnalysis::visit(ASTUnaryExprNode *node) { //assumptions of operators done here ,not specified in bnf , but jamlu iktar sens hekk
    node->getExpression()->accept(this);
    if(typeToBeChecked == Type::REAL || typeToBeChecked == Type::INT){
        if(node->getOp() != NegationOperator::MINUS){
            cout<<"not cannot be applied to number types , use minus instead"<<endl;
            exit(-1);
        }
    }else if(typeToBeChecked == Type::BOOL){
        if(node->getOp() != NegationOperator::NOT){
            cout<<"- cannot be applied to boolean expressions"<<endl;
            exit(-1);
        }
    }else{
        cout<<"- and not cannot be applied to strings"<<endl;
        exit(-1);
    }
}

void SemanticAnalysis::visit(ASTFnCallExprNode *node) {

}

void SemanticAnalysis::visitTree(vector<ASTStatementNode *> *tree) {
    ScopedTable.push_back(new SymbolTable());
    for (auto &i : *tree) {
        i->accept(this);
    }
    ScopedTable.pop_back();
    cout<<"Valid Program"<<endl;
}
