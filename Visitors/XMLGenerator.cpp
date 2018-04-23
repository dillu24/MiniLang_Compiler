//
// Created by Dylan Galea on 13/04/2018.
//

#include <iostream>
#include "XMLGenerator.h"

Visitors::XMLGenerator::XMLGenerator() {
    indentationLevel = ""; //start with no indentation
}

void Visitors::XMLGenerator::visitTree(vector<ASTStatementNode *> *tree) {
    cout<< "<?xml version=\"1.0\"?>"<<endl;//give version type
    cout<<"<AbstractSyntaxTree>"<<endl; //starting xml tag as type of root
    TabIn(); //go 1 tab in to signify child of root
    for (auto &subtree : *tree) {
        subtree->accept(this); //start accepting the statements
    }
    TabOut(); //go 1 tab out to signify end of converting xml
    cout<<"</AbstractSyntaxTree>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTAssignStatementNode *node) {
    cout<<indentationLevel<<"<Assign>"<<endl;
    TabIn(); //go in since an assign statement has 2 children , the identifier and expression
    node->getIdentifier()->accept(this); //visit identifier child
    node->getExpression()->accept(this); //visit expression child
    TabOut();
    cout<<indentationLevel<<"</Assign>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTBlockStatementNode *node) {
    cout<<indentationLevel<<"<Block>"<<endl;
    TabIn(); //tab in since a block has a number of statements attached to it that must be visited
    vector<ASTStatementNode*> statements = *node->getStatements(); //get block
    for (auto &statement : statements) {
        statement->accept(this); //visit each statement attached to the block
    }
    TabOut();
    cout<<indentationLevel<<"</Block>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTIfStatementNode *node) {
    cout<<indentationLevel<<"<If>"<<endl;
    TabIn(); //tab in since each if statement has at most 3 children , the expression child, if block and else block
    node->getExpression()->accept(this); //visit predicate node
    node->getTrueBlock()->accept(this); // visit if block
    if(node->getElseBlock() != nullptr){ //if the else block is present visit it.
        node->getElseBlock()->accept(this);
    }
    TabOut();
    cout<<indentationLevel<<"</If>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTPrintStatementNode *node) {
    cout<<indentationLevel<<"<print>"<<endl;
    TabIn(); //tab in since each print statement has a child expression to be printed
    node->getExpr()->accept(this); // visit child expression node.
    TabOut();
    cout<<indentationLevel<<"</print>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTVarDeclStatementNode *node) {
    cout<<indentationLevel<<"<VarDecl Type=\"";
    node->printType(); //type is not a child , only stored in the ASTVarDeclStatementNode therefore it must be in the same tag
    cout<<"\">"<<endl;
    TabIn(); //the ASTVarDeclStatement node has 2 children , the identifier to be assigned and the expression to be assigned to
    node->getIdentifier()->accept(this); //visit identifier node
    node->getExpr()->accept(this); //visit expression node
    TabOut();
    cout<<indentationLevel<<"</VarDecl>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTWhileStatementNode *node) {
    cout<<indentationLevel<<"<While>"<<endl;
    TabIn(); //the while statement node has 2 children , the expression node to be met and the block node to execute if predicate is true
    node->getExpression()->accept(this); //visit expression node
    node->getBlock()->accept(this); // visit block node
    TabOut();
    cout<<indentationLevel<<"</While>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTReturnStatementNode *node) {
    cout<<indentationLevel<<"<return>"<<endl;
    TabIn(); //tab in since return statement has expression node as child
    node->getExpression()->accept(this); //visit expression node
    TabOut();
    cout<<indentationLevel<<"</return>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTFuncDeclStatementNode *node) {
    cout<<indentationLevel<<"<FuncDecl Type=\""; //each function declaration has the return type , this is not a node and must
                                                 // be saved as on the same level of the ASTFuncDeclStatement node.
    node->printType();
    cout<<"\">"<<endl;
    TabIn();//tab in since the ASTFnDeclStatement node has a child identifier node storing the function name
    node->getIdentifier()->accept(this); //visit identifier
    FormalParams *fps = node->getFormalParams();
    FormalParam *fp;
    if(fps!= nullptr){ //if we have parameters
        fp = fps->getFormalParam();
        cout<<indentationLevel<<"<FormalParam Type=\""; //although the formal parameters are not a node , they have nodes attached to them , thus in order to make
                                                        // the output better visually , they were made on a different level than the ASTFnDeclStatementNode.
        fp->printType(); //print type of parameter on same level
        cout<<"\">"<<endl;
        TabIn();
        fp->getIdentifier()->accept(this); //print attached child identifer node on indented level
        TabOut();
        cout<<indentationLevel<<"</FormalParam>"<<endl; //finish sub branch
        for (auto &parameter : fps->parameters) { //do the same if there are remaining parameters.
            cout<<indentationLevel<<"<FormalParam Type=\"";
            parameter->printType();
            cout<<"\">"<<endl;
            TabIn();
            parameter->getIdentifier()->accept(this);
            TabOut();
            cout<<indentationLevel<<"</FormalParam>"<<endl;
        }
    }
    node->getBlock()->accept(this); //visit function definition block child branch
    TabOut();
    cout<<indentationLevel<<"</FuncDecl>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTBinaryExprNode *node) {
    if(node->getOperator() == Operators::LESSTHAN){ // if type is '<' this needs to be escaped in xml
        cout<<indentationLevel<<"<BinaryExp Op=\"&lt;\">"<<endl;
    }else{
        cout<<indentationLevel<<"<BinaryExp Op=\""; //otherwise print operator on same level of binary exp node , since
                                                    // type is not a node
        node->printOperator();
        cout<<"\">"<<endl;
    }
    TabIn(); // go in since the LHS and RHS are children expressions that need to be visited
    node->getLhs()->accept(this); // visit LHS
    node->getRhs()->accept(this);// visit RHS
    TabOut();
    cout<<indentationLevel<<"</BinaryExp>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTNumberExprNode *node) {
    cout<<indentationLevel<<"<NumberLiteral>"<<node->getValue()<<"</NumberLiteral>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTBooleanLiteralExpressionNode *node) {
    cout<<indentationLevel<<"<BoolLiteral>"<<node->getValue()<<"</BoolLiteral>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTStringLiteralExprNode *node) {
    cout<<indentationLevel<<"<StringLiteral>"<<node->getValue()<<"</StringLiteral>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTIdentifierExprNode *node) {
    cout<<indentationLevel<<"<Identifier>"<<node->getIdentifierName()<<"</Identifier>"<<endl;
}

void Visitors::XMLGenerator::visit(ASTSubExprNode *node) {
    cout<<indentationLevel<<"<SubExp>"<<endl;
    TabIn(); //tab in since sub expression has expression as child attached to it
    node->getSubExpr()->accept(this); //visit sub expression node
    TabOut();
    cout<<indentationLevel<<"</SubExp>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTUnaryExprNode *node) {
    cout<<indentationLevel<<"<UnaryExp Op=\""; //print negation operator on the same level of the node since this is not a separate node
    node->printNegOp();
    cout<<"\">"<<endl;
    TabIn(); //tab in since the expression node is a child attached to the unary expression node
    node->getExpression()->accept(this);
    TabOut();
    cout<<indentationLevel<<"</UnaryExp>"<<endl; //finish sub branch
}

void Visitors::XMLGenerator::visit(ASTFnCallExprNode *node) {
    cout<<indentationLevel<<"<FnCall>"<<endl;
    TabIn(); //go in since function call has an identifier as children and a number of parameters attached to it as children
    node->getIdentifier()->accept(this); //visit name of function node
    vector<ASTExprNode*> parameters = node->getParameters();
    for (auto &parameter : parameters) { //if there are parameters visit them
        parameter->accept(this);
    }
    TabOut();
    cout<<indentationLevel<<"</FnCall>"<<endl; // finish sub branch
}

void Visitors::XMLGenerator::TabIn() {
    indentationLevel.push_back('\t'); //add new tab
}

void Visitors::XMLGenerator::TabOut() {
    indentationLevel.pop_back(); // remove tab
}

