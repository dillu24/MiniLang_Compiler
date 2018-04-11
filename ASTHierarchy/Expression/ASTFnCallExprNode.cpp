//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTFnCallExprNode.h"
#include "../../Visitors/Visitor.h"

ASTFnCallExprNode::ASTFnCallExprNode(ASTIdentifierExprNode *identifier) {
    this->identifier = &* identifier;
    parameters = vector<ASTExprNode*>();
    this->expressionType = ExpressionType::FNCALL_EXP;
}

ASTFnCallExprNode::~ASTFnCallExprNode() {
    delete(identifier);
    for(unsigned int i=0;i<parameters.size();i++){
        delete parameters.at(i);
    }
}

void ASTFnCallExprNode::setIdentifier(ASTIdentifierExprNode *identifier) {
    this->identifier = &*identifier;
}

void ASTFnCallExprNode::addParameters(ASTExprNode *params) {
    parameters.push_back(params);
}

void ASTFnCallExprNode::removeParameter(int index) {
    parameters.erase(parameters.begin()+index);
}

vector<ASTExprNode *> ASTFnCallExprNode::getParameters() {
    return parameters;
}

ASTIdentifierExprNode *ASTFnCallExprNode::getIdentifier() {
    return identifier;
}

void ASTFnCallExprNode::accept(Visitor *v) {
    v->visit(this);
}
