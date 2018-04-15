//
// Created by Dylan Galea on 14/04/2018.
//

#include <cmath>
#include "SemanticAnalysis.h"

SemanticAnalysis::SemanticAnalysis(){
    ScopedTable = vector<SymbolTable*>();
    typeToBeChecked = Type::BOOL; //as start
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

void SemanticAnalysis::visit(ASTBlockStatementNode *node) { //in function declaration must do the parameters handler
    ScopedTable.push_back(new SymbolTable());
    vector<ASTStatementNode*> statements = *node->getStatements();
    for (auto &statement : statements) {
        statement->accept(this);
    }
    ScopedTable.pop_back();
}

void SemanticAnalysis::visit(ASTIfStatementNode *node) {
    node->getExpression()->accept(this);
    if(typeToBeChecked != Type::BOOL){
        cout<<"The if statement condition must be a predicate"<<endl;
        exit(-1);
    }
    node->getTrueBlock()->accept(this);
    if(node->getElseBlock() != nullptr){
        node->getElseBlock()->accept(this);
    }
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
    node->getExpression()->accept(this);
    if(typeToBeChecked != Type::BOOL){
        cout<<"The while statement condition must be a predicate"<<endl;
        exit(-1);
    }
    node->getBlock()->accept(this);
}

void SemanticAnalysis::visit(ASTReturnStatementNode *node) {
    node->getExpression()->accept(this);
}

void SemanticAnalysis::visit(ASTFuncDeclStatementNode *node) {

}

void SemanticAnalysis::visit(ASTBinaryExprNode *node) { //check binary operators while doing expressions for all sub part of expression
    node->getLhs()->accept(this);
    Type lhsType = typeToBeChecked;
    node->getRhs()->accept(this);
    Type rhsType = typeToBeChecked;
    if(lhsType != rhsType){
        cout<<"Binary operators can be only applied to expressions of the same type"<<endl;
        exit(-1);
    }
    switch(node->getOperator()){
        case Operators::PLUS:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The + operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = lhsType;
            }
            break;
        case Operators::MINUS:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The - operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = lhsType;
            }
            break;
        case Operators::OR:
            if(lhsType != Type::BOOL){
                cout<<"The or operator can only be used for bools"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = lhsType;
            }
            break;
        case Operators::LESSTHAN:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The < operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::GREATERTHAN:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The > operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::LESSTHANEQUAL:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The <= operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::GREATERTHANEQUAL:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The >= operator can only be used for number types"<<endl;
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::EQUALTO:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The == operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::NOTEQUAL:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The != operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::TIMES:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The * operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = lhsType;
            }
            break;
        case Operators::DIVISION: //division always gets real types to be safe , therefore programmer must be careful
                                  // of this.
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                cout<<"The / operator can only be used for number types"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = Type::REAL;
            }
            break;
        case Operators::AND:
            if(lhsType != Type::BOOL){
                cout<<"The and operator can only be used for bools"<<endl;
                exit(-1);
            }else{
                typeToBeChecked = lhsType;
            }
            break;
    }
}

void SemanticAnalysis::visit(ASTNumberExprNode *node) {
    double integerPart = 0.0;
    if(modf(node->getValue(),&integerPart)==0.0){
        typeToBeChecked =  Type::INT;
    }else{
        typeToBeChecked = Type::REAL;
    }
}

void SemanticAnalysis::visit(ASTBooleanLiteralExpressionNode*) {
    typeToBeChecked = Type::BOOL;
}

void SemanticAnalysis::visit(ASTStringLiteralExprNode*) {
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

void SemanticAnalysis::visit(ASTFnCallExprNode *node) { //be careful in funciton clal to check parametres , for number and type

}

void SemanticAnalysis::visitTree(vector<ASTStatementNode *> *tree) {
    ScopedTable.push_back(new SymbolTable());
    for (auto &i : *tree) {
        i->accept(this);
    }
    ScopedTable.pop_back();
    cout<<"Valid Program"<<endl;
}
