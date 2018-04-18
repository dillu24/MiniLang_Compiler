//
// Created by Dylan Galea on 17/04/2018.
//

#include <cmath>
#include "InterpreterExecutionPass.h"

InterpreterExecutionPass::InterpreterExecutionPass() {
    validator = new SemanticAnalysis();
    ScopedTable = vector<SymbolTable*>();
    returnStatementExecuted = false;
    realVals = vector<double>();
    boolVals = vector<bool>();
    stringVals = vector<string>();
    integerVals = vector<int>();
    lastEvaluatedType = Type::BOOL;
    functionParameters = nullptr;
    inIfstatement = false;
    inWhileStatement = false;
    queueOfParams = queue<TypeBinder::valueInIdentifier*>();
}

void InterpreterExecutionPass::visit(ASTAssignStatementNode *node) {
    unsigned int indexInScopeTable =0;
    for(int i=0;i<ScopedTable.size();i++){
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifier()->getIdentifierName(),TypeBinder::VARIABLE)){
            lastEvaluatedType = ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).getPrimitiveType();
            indexInScopeTable = ScopedTable.size()-i-1;
            break;
        }
    }
    node->getExpression()->accept(this);
    switch(lastEvaluatedType){
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
    ScopedTable.push_back(new SymbolTable());
    bool functionBlock = false;
    if(functionParameters != nullptr){
        if(functionParameters->getFormalParam() != nullptr){
            ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(functionParameters->getFormalParam()->getIdentifier()->getIdentifierName(),
                                                                   TypeBinder(functionParameters->getFormalParam()->getType(),
                                                                              TypeBinder::IdentifierType::VARIABLE));
            switch(functionParameters->getFormalParam()->getType()){
                case Type::REAL:
                    ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(functionParameters->getFormalParam()->getIdentifier()->
                            getIdentifierName()).setRealValue(queueOfParams.front()->realValue);
                    queueOfParams.pop();
                    break;
                case Type::INT:
                    ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(functionParameters->getFormalParam()->getIdentifier()->
                            getIdentifierName()).setIntValue(queueOfParams.front()->intValue);
                    queueOfParams.pop();
                    break;
                case Type::BOOL:
                    ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(functionParameters->getFormalParam()->getIdentifier()->
                            getIdentifierName()).setBoolValue(queueOfParams.front()->boolValue);
                    queueOfParams.pop();
                    break;
                case Type::STRING:
                    ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(functionParameters->getFormalParam()->getIdentifier()->
                            getIdentifierName()).setStringValue(queueOfParams.front()->stringValue);
                    queueOfParams.pop();
                    break;
            }
            functionBlock = true;
        }
        for (auto &parameter : functionParameters->parameters) {
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
    functionParameters = nullptr;
    vector<ASTStatementNode*> statements = *node->getStatements();
    for (auto &statement : statements) {
        statement->accept(this);
        if(returnStatementExecuted && (inIfstatement||inWhileStatement)){
            exit(0);
        }else if(returnStatementExecuted){
            returnStatementExecuted = false;
            return;
        }
    }
    if(!functionBlock){
        ScopedTable.pop_back();
    }
}

void InterpreterExecutionPass::visit(ASTIfStatementNode *node) {
    node->getExpression()->accept(this);
    inIfstatement = true;
    if(boolVals.at(boolVals.size()-1)){
        node->getTrueBlock()->accept(this);
    }else{
        if(node->getElseBlock()!= nullptr){
            node->getElseBlock()->accept(this);
        }
    }
    inIfstatement = false;
    boolVals.pop_back();
}

void InterpreterExecutionPass::visit(ASTPrintStatementNode *node) {
    node->getExpr()->accept(this);
    switch (lastEvaluatedType){
        case Type::REAL:
            cout<<realVals.at(0)<<endl;
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
    TypeBinder* tb;
    switch(lastEvaluatedType){
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
    node->getExpression()->accept(this);
    inWhileStatement = true;
    while(boolVals.at(boolVals.size()-1)) {
        node->getBlock()->accept(this);
        node->getExpression()->accept(this);
    }
    inWhileStatement =false;
    boolVals.pop_back();
}

void InterpreterExecutionPass::visit(ASTReturnStatementNode *node) {
    node->getExpression()->accept(this);
    returnStatementExecuted = true;
    ScopedTable.pop_back();
    if(ScopedTable.empty()) {
        exit(0);
    }
}

void InterpreterExecutionPass::visit(ASTFuncDeclStatementNode *node) {
    functionParameters = &*node->getFormalParams();
    auto tb = TypeBinder(node->getType(),TypeBinder::FUNCTION);
    if(functionParameters != nullptr){
        tb.parameterTypes.push_back(functionParameters->getFormalParam()->getType());
        for (auto &parameter : functionParameters->parameters) {
            tb.parameterTypes.push_back(parameter->getType());
        }
    }
    tb.setFormalParams(functionParameters);
    tb.setFnDefnBlock(node->getBlock());
    ScopedTable.at(ScopedTable.size()-1)->addToSymbolTable(node->getIdentifier()->getIdentifierName(),tb);
}

void InterpreterExecutionPass::visit(ASTBinaryExprNode *node) {
    node->getLhs()->accept(this);
    node->getRhs()->accept(this);
    bool operand1;
    bool operand2;
    switch (node->getOperator()){
        case Operators::PLUS:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                integerVals.push_back(op1+op2);
                lastEvaluatedType = Type::INT;
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                realVals.push_back(op1+op2);
                lastEvaluatedType = Type::REAL;
            }
            break;
        case Operators::MINUS:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                integerVals.push_back(op1-op2);
                lastEvaluatedType = Type::INT;
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                realVals.push_back(op1-op2);
                lastEvaluatedType = Type::REAL;
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
            lastEvaluatedType = Type::BOOL;
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
            lastEvaluatedType = Type::BOOL;
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
            lastEvaluatedType = Type::BOOL;
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
            lastEvaluatedType = Type::BOOL;
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
            lastEvaluatedType = Type::BOOL;
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
            lastEvaluatedType = Type::BOOL;
            break;
        case Operators::TIMES:
            if(lastEvaluatedType == Type::INT){
                int op1 = integerVals.at(integerVals.size()-2);
                int op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                integerVals.push_back(op1*op2);
                lastEvaluatedType = Type::INT;
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                realVals.push_back(op1*op2);
                lastEvaluatedType = Type::REAL;
            }
            break;
        case Operators::DIVISION:
            if(lastEvaluatedType == Type::INT){
                double op1 = integerVals.at(integerVals.size()-2);
                double op2 = integerVals.at(integerVals.size()-1);
                integerVals.pop_back();
                integerVals.pop_back();
                realVals.push_back(op1/op2);
                lastEvaluatedType = Type::REAL;
            }else if(lastEvaluatedType == Type::REAL){
                double op1 = realVals.at(realVals.size()-2);
                double op2 = realVals.at(realVals.size()-1);
                realVals.pop_back();
                realVals.pop_back();
                realVals.push_back(op1/op2);
                lastEvaluatedType = Type::REAL;
            }
            break;
        case Operators::AND:
            operand1 = boolVals.at(boolVals.size()-2);
            operand2 = boolVals.at(boolVals.size()-1);
            boolVals.pop_back();
            boolVals.pop_back();
            boolVals.push_back(operand1&&operand2);
            lastEvaluatedType = Type::BOOL;
            break;
        case Operators::OR:
            operand1 = boolVals.at(boolVals.size()-2);
            operand2 = boolVals.at(boolVals.size()-1);
            boolVals.pop_back();
            boolVals.pop_back();
            boolVals.push_back(operand1 || operand2);
            lastEvaluatedType = Type::BOOL;
            break;
    }
}

void InterpreterExecutionPass::visit(ASTNumberExprNode *node) {
    if(node->getNumberType() == ASTNumberExprNode::REAL){
        lastEvaluatedType = Type::REAL;
        realVals.push_back(node->getValue());
    }else if(node->getNumberType() == ASTNumberExprNode::INT){
        lastEvaluatedType = Type::INT;
        integerVals.push_back((int)node->getValue());
    }
    /*double integerPart = 0.0; //stores the integer part of the number
    if(modf(node->getValue(),&integerPart)==0.0){ //if the remainder part is 0 return int , otherwise real
        lastEvaluatedType = Type::INT;
        integerVals.push_back((int)integerPart);
    }else{
        lastEvaluatedType = Type::REAL;
        realVals.push_back(node->getValue());
    }*/
}

void InterpreterExecutionPass::visit(ASTBooleanLiteralExpressionNode *node) {
    lastEvaluatedType = Type::BOOL;
    boolVals.push_back(node->getValue());
}

void InterpreterExecutionPass::visit(ASTStringLiteralExprNode *node) {
    lastEvaluatedType = Type::STRING;
    stringVals.push_back(node->getValue());
}

void InterpreterExecutionPass::visit(ASTIdentifierExprNode *node) {
    unsigned int indexInScopeTable =0;
    for(int i=0;i<ScopedTable.size();i++){
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifierName(),TypeBinder::VARIABLE)){
            lastEvaluatedType = ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifierName()).getPrimitiveType();
            indexInScopeTable = ScopedTable.size()-i-1;
            break;
        }
    }
    switch(lastEvaluatedType){
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
    node->getSubExpr()->accept(this);
}

void InterpreterExecutionPass::visit(ASTUnaryExprNode *node) {
    node->getExpression()->accept(this);
    if(lastEvaluatedType == Type::BOOL){
        boolVals.at(boolVals.size()-1) = !boolVals.at(boolVals.size()-1);
    }else if(lastEvaluatedType == Type::INT){
        integerVals.at(integerVals.size()-1) = -integerVals.at(integerVals.size()-1);
    }else if(lastEvaluatedType==Type::REAL){
        realVals.at(realVals.size()-1) = -realVals.at(realVals.size()-1);
    }
}

void InterpreterExecutionPass::visit(ASTFnCallExprNode *node) {
    unsigned int tableIndex =0;
    for(unsigned int i=0;i<ScopedTable.size();i++){
        if(ScopedTable.at(ScopedTable.size()-i-1)->checkIfInSymbolTable(node->getIdentifier()->getIdentifierName(),TypeBinder::FUNCTION)){
            if(ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).parameterTypes.size()
               != node->getParameters().size()){
                continue;
            }
            bool badTypes = false;
            for(unsigned int j=0;j<node->getParameters().size();j++){
                auto *vi = new TypeBinder::valueInIdentifier();
                node->getParameters().at(j)->accept(this);
                switch(lastEvaluatedType){
                    case Type::REAL:
                        vi->realValue = realVals.at(realVals.size()-1);
                        realVals.pop_back();
                        queueOfParams.push(vi);
                        break;
                    case Type::INT:
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
                if(lastEvaluatedType != ScopedTable.at(ScopedTable.size()-i-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).parameterTypes.at(j)){
                    badTypes =true;
                    break;
                }
            }
            if(badTypes){
                continue;
            }
            tableIndex = ScopedTable.size()-i-1;
            break;
        }
    }
    functionParameters = &*ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName()).getFormalParams();
    ScopedTable.at(tableIndex)->getTypeBinder(node->getIdentifier()->getIdentifierName()).getFnDefnBlock()->accept(this);
    switch(lastEvaluatedType){
        case Type::REAL:
            ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setRealValue(realVals.at(realVals.size()-1));
            realVals.pop_back();
            break;
        case Type::INT:
            ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setIntValue(integerVals.at(integerVals.size()-1));
            integerVals.pop_back();
            break;
        case Type::BOOL:
            ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setBoolValue(boolVals.at(boolVals.size()-1));
            boolVals.pop_back();
            break;
        case Type::STRING:
            ScopedTable.at(ScopedTable.size()-1)->getTypeBinder(node->getIdentifier()->getIdentifierName()).setStringValue(stringVals.at(stringVals.size()-1));
            stringVals.pop_back();
            break;
    }
    node->getIdentifier()->accept(this);
}

void InterpreterExecutionPass::visitTree(vector<ASTStatementNode *> *tree) {
    validator->visitTree(tree);
    ScopedTable.push_back(new SymbolTable()); //create the global scope
    for (auto &i : *tree) {
        i->accept(this); //visit each statement in the AST
    }
    ScopedTable.pop_back(); //close the global branch
}
