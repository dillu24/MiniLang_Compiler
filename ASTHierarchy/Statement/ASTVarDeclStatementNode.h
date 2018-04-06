//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H

#include <string>
#include "../ASTStatementNode.h"
#include "Type.h"
#include "../ASTExprNode.h"

using namespace std;
namespace AST{
    class ASTVarDeclStatementNode:ASTStatementNode{
    private:
        string identifier;
        Type type;
        ASTExprNode* expression;
    public:
        ASTVarDeclStatementNode(string identifier,Type type,ASTExprNode* expr);
        ~ASTVarDeclStatementNode();
        void setIdentifier(string ident);
        void setType(Type type);
        void setExpr(ASTExprNode* expr);
        string getIdentifier();
        Type getType();
        ASTExprNode* getExpr();
        void accept(Visitor *v) override;
    };
}


#endif //COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H
