//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H

#include <string>
#include "../ASTStatementNode.h"
#include "../Type.h"
#include "../ASTExprNode.h"
#include "../Expression/ASTIdentifierExprNode.h"

using namespace std;
namespace AST{
    class ASTVarDeclStatementNode:public ASTStatementNode{
    private:
        ASTIdentifierExprNode *identifier;
        Type type;
        ASTExprNode* expression;
    public:
        ASTVarDeclStatementNode();
        ASTVarDeclStatementNode(ASTIdentifierExprNode *identifier,Type type,ASTExprNode* expr);
        ~ASTVarDeclStatementNode();
        void setIdentifier(AST::ASTIdentifierExprNode *ident);
        void setType(Type type);
        void setExpr(ASTExprNode* expr);
        ASTIdentifierExprNode* getIdentifier();
        Type getType();
        ASTExprNode* getExpr();
        void accept(Visitor *v) override;
    };
}


#endif //COMPILERSASSIGNMENT_ASTVARDECLSTATEMENTNODE_H
