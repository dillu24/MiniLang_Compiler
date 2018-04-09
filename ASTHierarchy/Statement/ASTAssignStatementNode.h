//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "../Expression/ASTIdentifierExprNode.h"
#include <string>
using namespace std;

namespace AST{
    class ASTAssignStatementNode: public ASTStatementNode {
    private:
        ASTIdentifierExprNode* identifier;
        ASTExprNode* expression;
    public:
        ASTAssignStatementNode(ASTIdentifierExprNode* ident,ASTExprNode* expr);
        ~ASTAssignStatementNode();
        void setIdentifier(ASTIdentifierExprNode* identifier);
        void setExpression(ASTExprNode* expr);
        ASTExprNode* getExpression();
        ASTIdentifierExprNode* getIdentifier();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H
