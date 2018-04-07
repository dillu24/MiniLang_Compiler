//
// Created by Dylan Galea on 04/04/2018.
//
#ifndef COMPILERSASSIGNMENT_VISITOR_H
#define COMPILERSASSIGNMENT_VISITOR_H

#include "../ASTHierarchy/Expression/ASTBinaryExprNode.h"
#include "../ASTHierarchy/Statement/ASTBlockStatementNode.h"
#include "../ASTHierarchy/Statement/ASTIfStatementNode.h"
#include "../ASTHierarchy/Statement/ASTPrintStatementNode.h"
#include "../ASTHierarchy/Statement/ASTVarDeclStatementNode.h"
#include "../ASTHierarchy/Statement/ASTWhileStatementNode.h"
#include "../ASTHierarchy/Statement/ASTAssignStatementNode.h"
#include "../ASTHierarchy/Expression/ASTNumberExprNode.h"
#include "../ASTHierarchy/Statement/ASTReturnStatementNode.h"
#include "../ASTHierarchy/Statement/ASTFuncDeclStatementNode.h"
#include "../ASTHierarchy/Expression/ASTBooleanLiteralExpressionNode.h"
#include "../ASTHierarchy/Expression/ASTStringLiteralExprNode.h"
#include "../ASTHierarchy/Expression/ASTIdentifierExprNode.h"
#include "../ASTHierarchy/Expression/ASTSubExprNode.h"
#include "../ASTHierarchy/Expression/ASTUnaryExprNode.h"
#include "../ASTHierarchy/Expression/ASTFnCallExprNode.h"

using namespace AST;
namespace Visitors{
    class Visitor {
    public:
        virtual void visit(ASTAssignStatementNode *node)=0;
        virtual void visit(ASTBlockStatementNode *node)=0;
        virtual void visit(ASTIfStatementNode *node)=0;
        virtual void visit(ASTPrintStatementNode *node)=0;
        virtual void visit(ASTVarDeclStatementNode *node) = 0;
        virtual void visit(ASTWhileStatementNode *node) = 0;
        virtual void visit(ASTReturnStatementNode *node) = 0;
        virtual void visit(ASTFuncDeclStatementNode *node) =0;
        virtual void visit(ASTBinaryExprNode *node) = 0;
        virtual void visit(ASTNumberExprNode* node) = 0;
        virtual void visit(ASTBooleanLiteralExpressionNode* node)=0;
        virtual void visit(ASTStringLiteralExprNode* node)=0;
        virtual void visit(ASTIdentifierExprNode* node)=0;
        virtual void visit(ASTSubExprNode* node) = 0;
        virtual void visit(ASTUnaryExprNode* node) = 0;
        virtual void visit(ASTFnCallExprNode* node)=0;
    };
}


#endif //COMPILERSASSIGNMENT_VISITOR_H
