//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include <string>
using namespace std;

namespace AST{
    class ASTAssignStatementNode:ASTStatementNode {
    private:
        string identifier;
        ASTExprNode* expression;
    public:
        ASTAssignStatementNode(string ident,ASTExprNode* expr);
        ~ASTAssignStatementNode();
        void setIdentifier(string identifier);
        void setExpression(ASTExprNode* expr);
        ASTExprNode* getExpression();
        string getIdentifier();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H
