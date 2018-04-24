//
// Created by Dylan Galea on 14/04/2018.
//

#include <cmath>
#include "SemanticAnalysis.h"
#include "../Exceptions/CompilingErrorException.h"

using namespace Exception;
SemanticAnalysis::SemanticAnalysis(){
    ScopedTable = vector<SymbolTable*>(); //create memory for scoped symbol table
    typeToBeChecked = Type::BOOL; //give any dummy value
    functionParameters = nullptr; // since we have met no function till now
    ScopedTable.push_back(new SymbolTable());
}

void SemanticAnalysis::visit(ASTAssignStatementNode *node) {
    node->getIdentifier()->accept(this); //visit identifier to check if it has been declared, and get it's type
    Type identifierType = typeToBeChecked; // store the type
    node->getExpression()->accept(this); // visit the expression to check it's type
    Type expressionType = typeToBeChecked; //store type
    if(identifierType != expressionType){ // if variable type and it's assigned expression are not the same we have a semantic error
                                          // note int and reals are different types and are not automatically type casted as specified
        throw CompilingErrorException("The identifier "+node->getIdentifier()->getIdentifierName()+" does not have the "
                " same type as expression");
    }
}

void SemanticAnalysis::visit(ASTBlockStatementNode *node) {
    ScopedTable.push_back(new SymbolTable()); //create new scope since we met a new block
    if(functionParameters != nullptr){ //if the function has parameters add them to symbol table
        if(functionParameters->getFormalParam() != nullptr){
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(functionParameters->getFormalParam()->getIdentifier()->getIdentifierName(),
                                                                   TypeBinder(functionParameters->getFormalParam()->getType(),
                                                                              TypeBinder::IdentifierType::VARIABLE));
        }
        for (auto &parameter : functionParameters->parameters) { //if we have parameters with the same name we have a semantic error,
                                                                 // otherwise add them to the symbol table.
            if(ScopedTable.at(ScopedTable.size()-1)->checkIfInSymbolTable(parameter->getIdentifier()->getIdentifierName(),TypeBinder::VARIABLE)){
                throw CompilingErrorException("A variable with name "+parameter->getIdentifier()->getIdentifierName()+" has already been declared in this scope ");
            }
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(parameter->getIdentifier()->getIdentifierName(),
                                                                   TypeBinder(parameter->getType(),
                                                                              TypeBinder::IdentifierType::VARIABLE));
        }
    }
    functionParameters = nullptr; //since the parameters have been handled , set to nullptr so other functions can
                                  // have their parameters handled in the same way.
    vector<ASTStatementNode*> statements = *node->getStatements(); //stores the statements making up the block
    for (auto &statement : statements) { // visit each statement in the block.
        statement->accept(this);
        //check whether the statement is a return statement , if it is and no return statements have be incurred , then
        // save the type and indicate we met a return statement
        if(statement->getStatementType() == ASTStatementNode::StatementType::RETURN_STMT && !isReturnPresent){
            isReturnPresent = true;
            returnType = typeToBeChecked;
        }else if(statement->getStatementType() == ASTReturnStatementNode::StatementType::RETURN_STMT && returnType != typeToBeChecked){
            //if there is a bad return statement inform the programmer;
            throw CompilingErrorException("Bad return type in function ");
        }
    }
    ScopedTable.pop_back();//remove scope since we are ready
}

void SemanticAnalysis::visit(ASTIfStatementNode *node) {
    bool ifReturn = false;
    bool elseReturn = false;
    node->getExpression()->accept(this); //visit the expression predicate
    if(typeToBeChecked != Type::BOOL){ // if the type is not a boolean we cannot determine if the condition is true or false
                                       // hence we get a semantic error
        throw CompilingErrorException("If statement condition must be a predicate");
    }
    auto* trueblock = node->getTrueBlock();
    auto* elseblock = node->getElseBlock();
    for (auto &i : *trueblock->getStatements()) {// check if we have return statements , if yes set it true
        if(i->getStatementType() == ASTStatementNode::StatementType::RETURN_STMT){
            ifReturn = true;
        }
    }
    node->getTrueBlock()->accept(this); // visit true block
    if(node->getElseBlock() != nullptr){ // if an else block exists visit it.
        for (auto &i : *elseblock->getStatements()) {
            if(i->getStatementType() == ASTStatementNode::StatementType::RETURN_STMT){
                elseReturn = true; //indicate there is return in else
            }
        }
        node->getElseBlock()->accept(this);
    }
    isReturnPresent = ifReturn && elseReturn; //set accordingly , for returns
}

void SemanticAnalysis::visit(ASTPrintStatementNode *node) {
    node->getExpr()->accept(this); //visit expression of print statement
}

void SemanticAnalysis::visit(ASTVarDeclStatementNode *node) {
    //if in the same scope the variable is being declared we have a variable that has already been declared with the same
    // name , we have a semantic error , (notelast scope is last element in vector).
    if(ScopedTable.at(ScopedTable.size()-1)->checkIfInSymbolTable(node->getIdentifier()->getIdentifierName(),TypeBinder::VARIABLE)){
        throw CompilingErrorException("A variable with name "+node->getIdentifier()->getIdentifierName()+" has already been declared in this scope ");
    }
    node->getExpr()->accept(this); //visit expression
    if(typeToBeChecked == node->getType()){ //if type of expression is equal to type of variable to be stored in ,
                                            // we have a valid declaration , so add it to the symbol table
        TypeBinder tb = TypeBinder(typeToBeChecked,TypeBinder::IdentifierType::VARIABLE);
        ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),tb);
    }else{ //otherwise , we have a semantic error
        throw CompilingErrorException("Type of variable "+node->getIdentifier()->getIdentifierName()+" does not match with expression");
    }
}

void SemanticAnalysis::visit(ASTWhileStatementNode *node) {
    node->getExpression()->accept(this); //visit expression , if type is not a boolean we cannot determine if the condition
                                         // is met or not , thus return semantic error
    if(typeToBeChecked != Type::BOOL){
        throw CompilingErrorException("The while statement condition must be a predicate");
    }
    node->getBlock()->accept(this); //visit block
}

void SemanticAnalysis::visit(ASTReturnStatementNode *node) {
    node->getExpression()->accept(this); //visit expression to check if semantically correct
}

void SemanticAnalysis::visit(ASTFuncDeclStatementNode *node) {
    //if a function with the name stored in the ASTFuncDeclStatementNode  has already been declared then we get a semantic error
    if(ScopedTable.at(ScopedTable.size()-1)->checkIfInSymbolTable(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION)){
        throw CompilingErrorException("A function with name "+node->getIdentifier()->getIdentifierName()+" has already been declared in this scope ");
    }
    functionParameters = &*node->getFormalParams(); //store function parameters
    auto tb = TypeBinder(node->getType(),TypeBinder::FUNCTION);
    if(functionParameters != nullptr){ //if we have parameters add them to the type binder parameters types
                                                         // in order to check them we have a function call
        tb.parameterTypes.push_back(functionParameters->getFormalParam()->getType());
        for (auto &parameter : functionParameters->parameters) { //add remaining parameters if there exists
            tb.parameterTypes.push_back(parameter->getType());
        }
    }
    ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),tb); // add function name to symbol table
    node->getBlock()->accept(this); //visit the block
    vector<ASTStatementNode*> statements = *node->getBlock()->getStatements(); //stores the statements in the function block
    if(!isReturnPresent){ //if we met no returns notify the user
        throw CompilingErrorException("You forgot return in "+node->getIdentifier()->getIdentifierName());
    }
    if(node->getType() != returnType){ // if we have a bad return type notify the user
        throw CompilingErrorException("The return type and signature type of function "+node->getIdentifier()->getIdentifierName()+" do not match");
    }
    isReturnPresent = false; //set back to false
}

void SemanticAnalysis::visit(ASTBinaryExprNode *node) {
    node->getLhs()->accept(this); //check the lhs
    Type lhsType = typeToBeChecked; //store it's type
    node->getRhs()->accept(this); //check rhs
    Type rhsType = typeToBeChecked; //store it's type
    if(lhsType != rhsType){ // if their types are not equal we cannot apply operators , since according to specification
                            // operators must be applied to the same types , no exception also for reals and int since
                            // minilang does not perform automatic type cast
        throw CompilingErrorException("Binary operators can only be applied to expressions of the same type");
    }
    switch(node->getOperator()){
        case Operators::PLUS:
            if(lhsType == Type::STRING || lhsType == Type::BOOL){ //plus can only be done for number types , otherwise semantic error
                throw CompilingErrorException("The + operator can only be used for number types");
            }else{
                typeToBeChecked = lhsType;
            }
            break;
        case Operators::MINUS: //minus can only be done for number types , otherwise semantic error
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                throw CompilingErrorException("The - operator can only be used for number types");
            }else{
                typeToBeChecked = lhsType;
            }
            break;
        case Operators::OR: //or can only be done to bools otherwise semantic error
            if(lhsType != Type::BOOL){
                throw CompilingErrorException("The or operator can only be used for bools");
            }else{
                typeToBeChecked = lhsType;
            }
            break;
        case Operators::LESSTHAN: //less than can only be done for number types
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                throw CompilingErrorException("The < operator can only be used for number types");
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::GREATERTHAN: //greater than can only be done for number types
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                throw CompilingErrorException("The > operator can only be used for number types");
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::LESSTHANEQUAL: //only done for number types
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                throw CompilingErrorException("The <= operator can only be used for number types");
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::GREATERTHANEQUAL://only done for number types
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                throw CompilingErrorException("The >= operator can only be used for number types");
            }else{
                typeToBeChecked = Type::BOOL;
            }
            break;
        case Operators::EQUALTO: // can be done for all types
            typeToBeChecked = Type::BOOL;
            break;
        case Operators::NOTEQUAL: //can be done for all types
            typeToBeChecked = Type::BOOL;
            break;
        case Operators::TIMES: //can only be done for number types
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                throw CompilingErrorException("The * operator can only be used for number types");
            }else{
                typeToBeChecked = lhsType;
            }
            break;
        case Operators::DIVISION: //division always gets real types to be safe since if we have 2 integers , the result
                                  // may be a real , for example 3/4. This is a small defect in this implementation
                                  // also can only be used for number types
            if(lhsType == Type::STRING || lhsType == Type::BOOL){
                throw CompilingErrorException("The / operator can only be used for number types");
            }else{
                typeToBeChecked = Type::REAL;
            }
            break;
        case Operators::AND: //And can only be done for bools
            if(lhsType != Type::BOOL){
                throw CompilingErrorException("The and operator can only be used for bools ");
            }else{
                typeToBeChecked = lhsType;
            }
            break;
    }
}

void SemanticAnalysis::visit(ASTNumberExprNode *node) {
    if(node->getNumberType() == ASTNumberExprNode::REAL){
        typeToBeChecked = Type::REAL;
    }else if(node->getNumberType() == ASTNumberExprNode::INT){
        typeToBeChecked = Type::INT;
    }
}

void SemanticAnalysis::visit(ASTBooleanLiteralExpressionNode*) {
    typeToBeChecked = Type::BOOL;
}

void SemanticAnalysis::visit(ASTStringLiteralExprNode*) {
    typeToBeChecked = Type::STRING;
}

void SemanticAnalysis::visit(ASTIdentifierExprNode *node) {
    for(int i=0;i<ScopedTable.size();i++){ //Check if variable is declared in some scope
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifierName(),TypeBinder::VARIABLE)){
            typeToBeChecked = ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifierName(),TypeBinder::VARIABLE).getPrimitiveType();
            //if found store it's type.
            return;
        }
    }
    throw CompilingErrorException("Variable "+node->getIdentifierName()+" was not declared");
}

void SemanticAnalysis::visit(ASTSubExprNode *node) {
    node->getSubExpr()->accept(this); //check type of sub expression
}

void SemanticAnalysis::visit(ASTUnaryExprNode *node) { //assumptions of operators done st - is only applied to number types
    // and not only for bools , altough not specified , this is much more practical
    node->getExpression()->accept(this); //check type of expression
    if(typeToBeChecked == Type::REAL || typeToBeChecked == Type::INT){ //if we get number types
        if(node->getOp() != NegationOperator::MINUS){ //only minus can be applied to number types , else semantic error
            throw CompilingErrorException("not cannot be applied to number types , use minus instead");
        }
    }else if(typeToBeChecked == Type::BOOL){ //if we get a bool type , only not can be applied as negation , therefore if
                                             // we find minus , we get a semantic error
        if(node->getOp() != NegationOperator::NOT){
            throw CompilingErrorException("- cannot be applied to boolean expressions");
        }
    }else{ //if a string is found we cannot apply -
        throw CompilingErrorException("- and not cannot be applied to strings");
    }
}

void SemanticAnalysis::visit(ASTFnCallExprNode *node) {
    bool functionFound = false; //stores whether the called funciton is found
    unsigned int tableIndex =0; //stores the scope table index of where the function is found
    for(unsigned int i=0;i<ScopedTable.size();i++){
        //if the a function with same name as the node is found , check if it has the same number of parameters and
        //same parameter types , otherwise continue searching since the function may be found in previously declared
        //scopes.
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION)){
            if(ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION).parameterTypes.size()
                    != node->getParameters().size()){ //check number of parameters
                continue;
            }
            bool badTypes = false;
            for(unsigned int j=0;j<node->getParameters().size();j++){ //check parameter types.
                node->getParameters().at(j)->accept(this);
                if(typeToBeChecked != ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION).parameterTypes.at(j)){
                    badTypes =true;
                    break;
                }
            }
            if(badTypes){
                continue;
            }
            functionFound = true; //indicate that function is found
            tableIndex = ScopedTable.size()-i-1; // stores the index
            break;
        }
    }
    if(functionFound){ //if function found check that the number of parameters and the parameter types are correct,
                       // this was repeated so that an appropiate error message can be displayed to the user.
        if(node->getParameters().size() != ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION).parameterTypes.size()){
            throw CompilingErrorException("parameters numbers mismatch in function "+node->getIdentifier()->getIdentifierName());
        }
        for(unsigned int i=0;i<node->getParameters().size();i++){
            node->getParameters().at(i)->accept(this);
            if(typeToBeChecked != ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION).parameterTypes.at(i)){
                throw CompilingErrorException("Parameter type mismatch in function "+node->getIdentifier()->getIdentifierName());
            }
        }
        typeToBeChecked = ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION).getPrimitiveType();
    }else{ // if not found , the user is notified.
        throw CompilingErrorException("Function "+node->getIdentifier()->getIdentifierName()+" with given parameters was not declared");
    }
}

void SemanticAnalysis::visitTree(vector<ASTStatementNode *> *tree) {
    for (auto &i : *tree) {
        i->accept(this); //visit each statement in the AST
    }
}

vector<SymbolTable *> SemanticAnalysis::getScopedTable() {
    return ScopedTable;
}

SemanticAnalysis::~SemanticAnalysis() {
    ScopedTable.pop_back();
}
