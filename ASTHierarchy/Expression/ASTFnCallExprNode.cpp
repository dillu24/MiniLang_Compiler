//
// Created by Dylan Galea on 07/04/2018.
//

#include "ASTFnCallExprNode.h"
#include "../../Visitors/Visitor.h"

ASTFnCallExprNode::ASTFnCallExprNode(ASTIdentifierExprNode *identifier) {
    this->identifier = &* identifier;
    parameters = vector<ASTExprNode*>(); //initialize empty list of parameters
    this->expressionType = ExpressionType::FNCALL_EXP; // give appropriate expression type
}

ASTFnCallExprNode::~ASTFnCallExprNode() {
    delete(identifier);
    for (auto &parameter : parameters) { //delete all paramters from the heap
        delete parameter;
    }
}

void ASTFnCallExprNode::setIdentifier(ASTIdentifierExprNode *identifier) {
    this->identifier = &*identifier;
}

void ASTFnCallExprNode::addParameters(ASTExprNode *params) {
    parameters.push_back(params);
}


vector<ASTExprNode *> ASTFnCallExprNode::getParameters() {
    return parameters;
}

ASTIdentifierExprNode *ASTFnCallExprNode::getIdentifier() {
    return identifier;
}

void ASTFnCallExprNode::accept(Visitor *v) { //call the visitor's implementation when visiting such node.
    v->visit(this);
}
