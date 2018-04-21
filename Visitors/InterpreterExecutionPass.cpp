//
// Created by Dylan Galea on 17/04/2018.
//

#include <cmath>
#include "InterpreterExecutionPass.h"

InterpreterExecutionPass::InterpreterExecutionPass() {
    //Allocate vectors and queues memory and give any initial value to the variables.
    validator = new SemanticAnalysis();
    ScopedTable = vector<SymbolTable*>();
    realVals = vector<double>();
    boolVals = vector<bool>();
    stringVals = vector<string>();
    integerVals = vector<int>();
    lastEvaluatedType = Type::BOOL;
    queueOfParams = queue<TypeBinder::valueInIdentifier*>();
    functionParameters = nullptr;
    createGlobalScope();
}

void InterpreterExecutionPass::visit(ASTAssignStatementNode *node) {
    unsigned int indexInScopeTable =0; //this stores the index of the scope table the variable is in
    for(int i=0;i<ScopedTable.size();i++){
        //find the variable , since semantics are correct it must be found
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifier()->getIdentifierName(),TypeBinder::VARIABLE)){
            lastEvaluatedType = ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).getPrimitiveType();
            indexInScopeTable = ScopedTable.size()-i-1; // store the index
            break;
        }
    }
    node->getExpression()->accept(this); //visit the expression to be assigned
    switch(lastEvaluatedType){ // according to the type of the expression, store the value of the expression in the
                               // identifier's mapped value and pop that vector storing values.
        case Type::REAL:
            ScopedTable.at(indexInScopeTable)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setRealValue(realVals.at(realVals.size()-1));
            realVals.pop_back();
            break;
        case Type::INT:
            ScopedTable.at(indexInScopeTable)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setIntValue(integerVals.at(integerVals.size()-1));
            integerVals.pop_back();
            break;
        case Type::BOOL:
            ScopedTable.at(indexInScopeTable)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setBoolValue(boolVals.at(boolVals.size()-1));
            boolVals.pop_back();
            break;
        case Type::STRING:
            ScopedTable.at(indexInScopeTable)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setStringValue(stringVals.at(stringVals.size()-1));
            stringVals.pop_back();
            break;
    }
}

void InterpreterExecutionPass::visit(ASTBlockStatementNode *node) {
    ScopedTable.push_back(new SymbolTable()); //open a new scope since a new block is identified
    if(functionParameters != nullptr){
        if(functionParameters->getFormalParam() != nullptr){ //if there are parameters add them to the block
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(functionParameters->getFormalParam()->getIdentifier()->getIdentifierName(),
                                                                   TypeBinder(functionParameters->getFormalParam()->getType(),
                                                                              TypeBinder::IdentifierType::VARIABLE));
            switch(functionParameters->getFormalParam()->getType()) { // save the value of the identifier in the hash map
                case Type::REAL:
                    ScopedTable.at(ScopedTable.size() - 1)->getTypeBinder(
                            functionParameters->getFormalParam()->getIdentifier()->
                                    getIdentifierName()).setRealValue(queueOfParams.front()->realValue);
                    queueOfParams.pop();
                    break;
                case Type::INT:
                    ScopedTable.at(ScopedTable.size() - 1)->getTypeBinder(
                            functionParameters->getFormalParam()->getIdentifier()->
                                    getIdentifierName()).setIntValue(queueOfParams.front()->intValue);
                    queueOfParams.pop();
                    break;
                case Type::BOOL:
                    ScopedTable.at(ScopedTable.size() - 1)->getTypeBinder(
                            functionParameters->getFormalParam()->getIdentifier()->
                                    getIdentifierName()).setBoolValue(queueOfParams.front()->boolValue);
                    queueOfParams.pop();
                    break;
                case Type::STRING:
                    ScopedTable.at(ScopedTable.size() - 1)->getTypeBinder(
                            functionParameters->getFormalParam()->getIdentifier()->
                                    getIdentifierName()).setStringValue(queueOfParams.front()->stringValue);
                    queueOfParams.pop();
                    break;
            }
        }
        for (auto &parameter : functionParameters->parameters) { //do the same for the remaining parameters
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(parameter->getIdentifier()->getIdentifierName(),
                                                                   TypeBinder(parameter->getType(),
                                                                              TypeBinder::IdentifierType::VARIABLE));
            switch(parameter->getType()){
                case Type::REAL:
                    ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(parameter->getIdentifier()->
                            getIdentifierName()).setRealValue(queueOfParams.front()->realValue);
                    queueOfParams.pop();
                    break;
                case Type::INT:
                    ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(parameter->getIdentifier()->
                            getIdentifierName()).setIntValue(queueOfParams.front()->intValue);
                    queueOfParams.pop();
                    break;
                case Type::BOOL:
                    ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(parameter->getIdentifier()->
                            getIdentifierName()).setBoolValue(queueOfParams.front()->boolValue);
                    queueOfParams.pop();
                    break;
                case Type::STRING:
                    ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(parameter->getIdentifier()->
                            getIdentifierName()).setStringValue(queueOfParams.front()->stringValue);
                    queueOfParams.pop();
                    break;
            }
        }
    }
    functionParameters = nullptr; //set to nullptr so that if a function definition is inside another function we can
                                  //add parameters if the inside function has paramters in the definition.
    vector<ASTStatementNode*> statements = *node->getStatements();
    for (auto &statement : statements) {
        statement->accept(this); //visit each statement in the block
        if(isReturnPresent){ // if a return is identified , then we need to break from the scope since the remaining
                             // statements are unreachable
            break;
        }
    }
    ScopedTable.pop_back(); // remove scope since we are exiting the block
}

void InterpreterExecutionPass::visit(ASTIfStatementNode *node) {
    node->getExpression()->accept(this); //visit expression
    if(boolVals.at(boolVals.size()-1)){ // if it is evaluated to true visit the true block
        node->getTrueBlock()->accept(this);
    }else{ //else if there is an else block visit the else block
        if(node->getElseBlock()!= nullptr){
            node->getElseBlock()->accept(this);
        }
    }
    boolVals.pop_back(); // remove the expression's predicate result from the bools vector
}

void InterpreterExecutionPass::visit(ASTPrintStatementNode *node) {
    node->getExpr()->accept(this); //visit the expression to be printed
    switch (lastEvaluatedType){ //according to it's type, get the value from the vector and pop the vector
        case Type::REAL:
            cout<<realVals.at(0)<<endl; // the value is always made to be stored as the first value , since prior to printing
                                        // the result vector always has exactly one element
            realVals.pop_back();
            break;
        case Type::INT:
            cout<<integerVals.at(0)<<endl;
            integerVals.pop_back();
            break;
        case Type::BOOL:
            cout<<boolVals.at(0)<<endl;
            boolVals.pop_back();
            break;
        case Type::STRING:
            cout<<stringVals.at(0)<<endl;
            stringVals.pop_back();
            break;
    }
}

void InterpreterExecutionPass::visit(ASTVarDeclStatementNode *node) {
    node->getExpr()->accept(this); //visit expression
    TypeBinder* tb; //the matched value of the identifier in the hash map
    switch(lastEvaluatedType){
        // according to the expression type , store the value of the expression in the type binder and add it to the
            //current scope , also remove the value from the vector so that it is not mistakenly used by another method
        case Type::REAL:
            tb = new TypeBinder(lastEvaluatedType,TypeBinder::IdentifierType::VARIABLE);
            tb->setRealValue(realVals.at(realVals.size()-1));
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),*tb);
            realVals.pop_back();
            break;
        case Type::INT:
            tb = new TypeBinder(lastEvaluatedType,TypeBinder::IdentifierType::VARIABLE);
            tb->setIntValue(integerVals.at(integerVals.size()-1));
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),*tb);
            integerVals.pop_back();
            break;
        case Type::BOOL:
            tb = new TypeBinder(lastEvaluatedType,TypeBinder::IdentifierType::VARIABLE);
            tb->setBoolValue(boolVals.at(boolVals.size()-1));
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),*tb);
            boolVals.pop_back();
            break;
        case Type::STRING:
            tb = new TypeBinder(lastEvaluatedType,TypeBinder::IdentifierType::VARIABLE);
            tb->setStringValue(stringVals.at(stringVals.size()-1));
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),*tb);
            stringVals.pop_back();
            break;
    }
}

void InterpreterExecutionPass::visit(ASTWhileStatementNode *node) {
    node->getExpression()->accept(this); //get the expression
    while(boolVals.at(boolVals.size()-1)) { // if it is evaluated to true visit it's block and again evaluate the expression
                                            // and repeat untill the predicate is evaluated to false.
        node->getBlock()->accept(this);
        boolVals.pop_back(); // remove value so that we do not get a lot of boolean values in the vector
        node->getExpression()->accept(this);
    }
    boolVals.pop_back(); //remove value of predicate store in the bools
}

void InterpreterExecutionPass::visit(ASTReturnStatementNode *node) {
    node->getExpression()->accept(this); // visit expression to be returned
    isReturnPresent = true; // indicate that we found a return statement to act accordingly.
}

void InterpreterExecutionPass::visit(ASTFuncDeclStatementNode *node) {
    FormalParams* functionParameters = &*node->getFormalParams();
    auto tb = TypeBinder(node->getType(),TypeBinder::FUNCTION); // create a new type binder of type function
    if(functionParameters != nullptr){
        tb.parameterTypes.push_back(functionParameters->getFormalParam()->getType()); // push the parameters to the type binder
        for (auto &parameter : functionParameters->parameters) {
            tb.parameterTypes.push_back(parameter->getType());
        }
    }
    tb.setFormalParams(functionParameters); // store the parameters so that when we enter the block we can push them to
                                            // the next scope
    tb.setFnDefnBlock(node->getBlock()); //store the function block so that when calling it we can visit it
    ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),tb); // store the function in the
    //current scope it is defined
}

void InterpreterExecutionPass::visit(ASTBinaryExprNode *node) {
    node->getLhs()->accept(this); //visit left hand side of the expression
    node->getRhs()->accept(this); // visit right hand side of the expression
    bool operand1; // stores one of the operands in case of boolean
    bool operand2; // stores one of the operands in case of boolean
    switch (node->getOperator()){
        case Operators::PLUS:
            if(lastEvaluatedType == Type::INT){ // according to the type get the 2 operands from the respective vector
                                                // and do the operation
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                integerVals.push_back(op1+op2);
                lastEvaluatedType = Type::INT; // the result of an integer addition is an integer number
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                realVals.push_back(op1+op2);
                lastEvaluatedType = Type::REAL; // the result of a real addition is a real number
            }
            break;
        case Operators::MINUS:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                integerVals.push_back(op1-op2);
                lastEvaluatedType = Type::INT; //the result of an integer subtraction is an integer
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                realVals.push_back(op1-op2);
                lastEvaluatedType = Type::REAL; // the result of a real subtration is a real (to be kept simple)
            }
            break;
        case Operators::LESSTHAN:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                boolVals.push_back(op1<op2);
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                boolVals.push_back(op1<op2);
            }
            lastEvaluatedType = Type::BOOL; //when using relop , the result is a boolean type
            break;
        case Operators::GREATERTHAN:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                boolVals.push_back(op1>op2);
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                boolVals.push_back(op1>op2);
            }
            lastEvaluatedType = Type::BOOL; //when using relops the result is a boolean
            break;
        case Operators::LESSTHANEQUAL:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                boolVals.push_back(op1<=op2);
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                boolVals.push_back(op1<=op2);
            }
            lastEvaluatedType = Type::BOOL; // when using relops the result is a boolean
            break;
        case Operators::GREATERTHANEQUAL:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                boolVals.push_back(op1>=op2);
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                boolVals.push_back(op1>=op2);
            }
            lastEvaluatedType = Type::BOOL; // when using relops the result is a boolean
            break;
        case Operators::EQUALTO:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                boolVals.push_back(op1==op2);
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                boolVals.push_back(op1==op2);
            }else if(lastEvaluatedType ==Type::STRING){
                string op1 = stringVals.at(stringVals.size()-2);
                string op2 = stringVals.at(stringVals.size()-1);
                stringVals.pop_back();
                stringVals.pop_back();
                boolVals.push_back(op1==op2);
            }else if(lastEvaluatedType == Type::BOOL){
                operand1 = boolVals.at(boolVals.size()-2);
                operand2 = boolVals.at(boolVals.size()-1);
                boolVals.pop_back();
                boolVals.pop_back();
                boolVals.push_back(operand1==operand2);
            }
            lastEvaluatedType = Type::BOOL; // when using relops the result type is boolean
            break;
        case Operators::NOTEQUAL:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                boolVals.push_back(op1!=op2);
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                boolVals.push_back(op1!=op2);
            }else if(lastEvaluatedType ==Type::STRING){
                string op1 = stringVals.at(stringVals.size()-2);
                string op2 = stringVals.at(stringVals.size()-1);
                stringVals.pop_back();
                stringVals.pop_back();
                boolVals.push_back(op1!=op2);
            }else if(lastEvaluatedType == Type::BOOL){
                operand1 = boolVals.at(boolVals.size()-2);
                operand2 = boolVals.at(boolVals.size()-1);
                boolVals.pop_back();
                boolVals.pop_back();
                boolVals.push_back(operand1!=operand2);
            }
            lastEvaluatedType = Type::BOOL; // when using relops the result type is boolean
            break;
        case Operators::TIMES:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                integerVals.push_back(op1*op2);
                lastEvaluatedType = Type::INT; // if we have done an integer multiplication the result is an integer
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                realVals.push_back(op1*op2);
                lastEvaluatedType = Type::REAL; // if we have done a real multiplication the result is a real number.
            }
            break;
        case Operators::DIVISION:
            if(lastEvaluatedType == Type::INT){
                double op1 = integerVals.at(integerVals.size()-2);
                double op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                realVals.push_back(op1/op2);
                lastEvaluatedType = Type::REAL; // when dividing the result is always real for simplicity , since for
                                                // example 3/4 is real and thus no way of classifying could be tought of
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                realVals.push_back(op1/op2);
                lastEvaluatedType = Type::REAL; // when dividing the result is always real for simplicity
            }
            break;
        case Operators::AND:
            operand1 = boolVals.at(boolVals.size()-2);
            operand2 = boolVals.at(boolVals.size()-1);
            boolVals.pop_back();
            boolVals.pop_back();
            boolVals.push_back(operand1&&operand2);
            lastEvaluatedType = Type::BOOL; // when doing and the result is a boolean
            break;
        case Operators::OR:
            operand1 = boolVals.at(boolVals.size()-2);
            operand2 = boolVals.at(boolVals.size()-1);
            boolVals.pop_back();
            boolVals.pop_back();
            boolVals.push_back(operand1 || operand2);
            lastEvaluatedType = Type::BOOL; // when doing or the result is a boolean
            break;
    }
    //Note due to precedence , expressions that include 'and' and 'or' must be carried out in brackets , since
    // for example (n==0) or (n==1) is not the same as n==0 or n==1 since 'or' has higher precedence than == from the
    //ebnf
}

void InterpreterExecutionPass::visit(ASTNumberExprNode *node) {
    if(node->getNumberType() == ASTNumberExprNode::REAL){ // if number type in node is real .. push the value to real vector
                                                          // and declare the expression as real
        lastEvaluatedType = Type::REAL;
        realVals.push_back(node->getValue());
    }else if(node->getNumberType() == ASTNumberExprNode::INT){ // if number type in node is int .. push the value to int vector
                                                               // and declare the expression as integer
        lastEvaluatedType = Type::INT;
        integerVals.push_back((int)node->getValue());
    }
}

void InterpreterExecutionPass::visit(ASTBooleanLiteralExpressionNode *node) {
    lastEvaluatedType = Type::BOOL; // if we met a boolean literal , identify the expression type as boolean
    boolVals.push_back(node->getValue()); // push the value to the bools vector , since it may need further processing
}

void InterpreterExecutionPass::visit(ASTStringLiteralExprNode *node) {
    lastEvaluatedType = Type::STRING; //if we met a string literal ,identify the expression type as string
    stringVals.push_back(node->getValue()); // push the value to the strings vector , since it may need further processing
}

void InterpreterExecutionPass::visit(ASTIdentifierExprNode *node) {
    // note that this method is only for variables , functions will be treated differently in function calls for simplicity
    unsigned int indexInScopeTable =0; // stores in which scope index , the variable is found .. searching is done
                                       // from inner scope to the outward scope , since inner scope variables hide outer scope variables
    for(int i=0;i<ScopedTable.size();i++){
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifierName(),TypeBinder::VARIABLE)){
            lastEvaluatedType = ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifierName()).getPrimitiveType(); //get type of variable
            indexInScopeTable = ScopedTable.size()-i-1; // store index
            break;
        }
    }
    switch(lastEvaluatedType){ // push the value on respective vector type according to the type of the variable
        case Type::REAL:
            realVals.push_back(ScopedTable.at(indexInScopeTable)->getTypeBinder(node->getIdentifierName()).getValueInIdentifier()->realValue);
            break;
        case Type::INT:
            integerVals.push_back(ScopedTable.at(indexInScopeTable)->getTypeBinder(node->getIdentifierName()).getValueInIdentifier()->intValue);
            break;
        case Type::BOOL:
            boolVals.push_back(ScopedTable.at(indexInScopeTable)->getTypeBinder(node->getIdentifierName()).getValueInIdentifier()->boolValue);
            break;
        case Type::STRING:
            stringVals.push_back(ScopedTable.at(indexInScopeTable)->getTypeBinder(node->getIdentifierName()).getValueInIdentifier()->stringValue);
            break;
    }
}

void InterpreterExecutionPass::visit(ASTSubExprNode *node) {
    node->getSubExpr()->accept(this); // visit expression , no further processing is needed
}

void InterpreterExecutionPass::visit(ASTUnaryExprNode *node) {
    node->getExpression()->accept(this); // visit expression
    if(lastEvaluatedType == Type::BOOL){ // if expression is bool, value in the bools vector must be negated with a not
        boolVals.at(boolVals.size()-1) = !boolVals.at(boolVals.size()-1);
    }else if(lastEvaluatedType == Type::INT){ // if expression is an integer the value in the integer vector must be negated with a -
        integerVals.at(integerVals.size()-1) = -integerVals.at(integerVals.size()-1);
    }else if(lastEvaluatedType==Type::REAL){ // reals are treated like integers for negation
        realVals.at(realVals.size()-1) = -realVals.at(realVals.size()-1);
    }
}

void InterpreterExecutionPass::visit(ASTFnCallExprNode *node) {
    queue<TypeBinder::valueInIdentifier*> tempQueue; // stores the queue state before going in a new function , this is
                                                     // done since , a parameter can be a function call , thus the wrong
                                                     // parameters may be evaluated in the function call , since a queue is used.
    unsigned int tableIndex =0; // stores were in the scope table the function resides.
    for(unsigned int i=0;i<ScopedTable.size();i++){
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION)){
            if(ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).parameterTypes.size()
               != node->getParameters().size()){
                continue;
            } // check if function has correct number of parameters
            bool badTypes = false;
            for(unsigned int j=0;j<node->getParameters().size();j++){
                auto *vi = new TypeBinder::valueInIdentifier();
                tempQueue = queueOfParams; // store state of queue
                queueOfParams = queue<TypeBinder::valueInIdentifier*>(); // declare empty queue in case the parameter is a function call
                node->getParameters().at(j)->accept(this); // visit first parameter
                if(lastEvaluatedType != ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).parameterTypes.at(j)){
                    badTypes =true; // if the first parameter type is not equal to the node's first parameter then we chose a wrong function , therefore break
                                    // and search again
                    break;
                }
                queueOfParams = tempQueue; // if everything is find get the state of the queue back
                switch(lastEvaluatedType){
                    case Type::REAL:
                        vi->realValue = realVals.at(realVals.size()-1); //store the value in vi
                        realVals.pop_back(); // pop the value of the parameter
                        queueOfParams.push(vi); // add value of last evaluated parameter to the queue
                        break;
                    case Type::INT: // the same is done as described for reals
                        vi->intValue = integerVals.at(integerVals.size()-1);
                        integerVals.pop_back();
                        queueOfParams.push(vi);
                        break;
                    case Type::BOOL:
                        vi->boolValue = boolVals.at(boolVals.size()-1);
                        boolVals.pop_back();
                        queueOfParams.push(vi);
                        break;
                    case Type::STRING:
                        vi->stringValue = stringVals.at(stringVals.size()-1);
                        stringVals.pop_back();
                        queueOfParams.push(vi);
                        break;
                }
            }
            if(badTypes){ // continue searching if we found the wrong function
                continue;
            }
            tableIndex = ScopedTable.size()-i-1; // store the scoped table index where the function was found
            break;
        }
    }
    functionParameters = &*ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName()).getFormalParams(); // store the parameters so that they will be entered in the next block
    ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName()).getFnDefnBlock()->accept(this); // visit block of the function call
    isReturnPresent = false; // make return false since if we have a function inside a function , the outer function still needs a return statement
    switch(lastEvaluatedType){ // store the function value in the identifier's mapped value in the hash map
        case Type::REAL:
            ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setRealValue(realVals.at(realVals.size()-1));
            break;
        case Type::INT:
            ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setIntValue(integerVals.at(integerVals.size()-1));
            break;
        case Type::BOOL:
            ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setBoolValue(boolVals.at(boolVals.size()-1));
            break;
        case Type::STRING:
            ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setStringValue(stringVals.at(stringVals.size()-1));
            break;
    }
}

void InterpreterExecutionPass::visitTree(vector<ASTStatementNode *> *tree) {
    validator->visitTree(tree); // check first that the tree is a valid program
    for (auto &i : *tree) {
        if(isReturnPresent){ //if there is a return in the global scope , is return is true ..therefore all remaining statements are unreachable .. therefore exit
            exit(0);
        }
        i->accept(this); //visit each statement in the AST
    }
}

void InterpreterExecutionPass::createGlobalScope() {
    ScopedTable.push_back(new SymbolTable());
}

void InterpreterExecutionPass::destroyGlobalScope() {
    ScopedTable.pop_back();
}

InterpreterExecutionPass::~InterpreterExecutionPass() {
    destroyGlobalScope();
}

SemanticAnalysis *InterpreterExecutionPass::getValidator() {
    return validator;
}
