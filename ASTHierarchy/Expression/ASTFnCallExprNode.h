//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTFNCALLEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTFNCALLEXPRNODE_H

#include <vector>
#include "ASTIdentifierExprNode.h"

namespace AST{
    class ASTFnCallExprNode:public ASTExprNode {
    private:
        ASTIdentifierExprNode* identifier;
        vector<ASTExprNode*> parameters;
    public:
        explicit ASTFnCallExprNode(ASTIdentifierExprNode* identifier);
        ~ASTFnCallExprNode();
        void setIdentifier(ASTIdentifierExprNode* identifier);
        void addParameters(ASTExprNode* params);
        void removeParameter(int index);
        vector<ASTExprNode*> getParameters();
        ASTIdentifierExprNode* getIdentifier();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTFNCALLEXPRNODE_H
