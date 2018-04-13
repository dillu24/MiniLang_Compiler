//
// Created by Dylan Galea on 04/04/2018.
//

/**
 * This is the Visitor virtual class. This is made virtual so that every Visitor that is created as a child of this
 * class must implement all the functions in this class . Thus this class acts as a blue print to all visitor classes.
 */

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
        /**
         * This method is used by the visitor whenever he visits an ASTAssignStatementNode
         * @param node
         * Stores the address of the ASTAssignStatementNode to be visited
         */
        virtual void visit(ASTAssignStatementNode *node)=0;
        /**
        * This method is used by the visitor whenever he visits an ASTBlockStatementNode
        * @param node
        * Stores the address of the ASTBlockStatementNode to be visited
        */
        virtual void visit(ASTBlockStatementNode *node)=0;
        /**
        * This method is used by the visitor whenever he visits an ASTIfStatementNode
        * @param node
        * Stores the address of the ASTIfStatementNode to be visited
        */
        virtual void visit(ASTIfStatementNode *node)=0;
        /**
        * This method is used by the visitor whenever he visits an ASTPrintStatementNode
        * @param node
        * Stores the address of the ASTPrintStatementNode to be visited
        */
        virtual void visit(ASTPrintStatementNode *node)=0;
        /**
        * This method is used by the visitor whenever he visits an ASTVarDeclStatementNode
        * @param node
        * Stores the address of the ASTVarDeclStatementNode to be visited
        */
        virtual void visit(ASTVarDeclStatementNode *node) = 0;
        /**
        * This method is used by the visitor whenever he visits an ASTWhileStatementNode
        * @param node
        * Stores the address of the ASTWhileStatementNode to be visited
        */
        virtual void visit(ASTWhileStatementNode *node) = 0;
        /**
        * This method is used by the visitor whenever he visits an ASTReturnStatementNode
        * @param node
        * Stores the address of the ASTReturnStatement to be visited
        */
        virtual void visit(ASTReturnStatementNode *node) = 0;
        /**
        * This method is used by the visitor whenever he visits an ASTFuncDeclStatementNode
        * @param node
        * Stores the address of the ASTFuncDeclStatementNode to be visited
        */
        virtual void visit(ASTFuncDeclStatementNode *node) =0;
        /**
        * This method is used by the visitor whenever he visits an ASTBinaryExprNode
        * @param node
        * Stores the address of the ASTBinaryExpr to be visited
        */
        virtual void visit(ASTBinaryExprNode *node) = 0;
        /**
        * This method is used by the visitor whenever he visits an ASTNumberExprNode
        * @param node
        * Stores the address of the ASTNumberExprNode to be visited
        */
        virtual void visit(ASTNumberExprNode* node) = 0;
        /**
        * This method is used by the visitor whenever he visits an ASTBooleanLiteralExpressionNode
        * @param node
        * Stores the address of the ASTBooleanLiteralExpressionNode to be visited
        */
        virtual void visit(ASTBooleanLiteralExpressionNode* node)=0;
        /**
        * This method is used by the visitor whenever he visits an ASTStringLiteralExprNode
        * @param node
        * Stores the address of the ASTStringLiteralExpr to be visited
        */
        virtual void visit(ASTStringLiteralExprNode* node)=0;
        /**
        * This method is used by the visitor whenever he visits an ASTIdentifierExprNode
        * @param node
        * Stores the address of the ASTIdentifierExprNode to be visited
        */
        virtual void visit(ASTIdentifierExprNode* node)=0;
        /**
        * This method is used by the visitor whenever he visits an ASTSubExprNode
        * @param node
        * Stores the address of the ASTSubExprNode to be visited
        */
        virtual void visit(ASTSubExprNode* node) = 0;
        /**
        * This method is used by the visitor whenever he visits an ASTUnaryExprNode
        * @param node
        * Stores the address of the ASTUnaryExprNode to be visited
        */
        virtual void visit(ASTUnaryExprNode* node) = 0;
        /**
        * This method is used by the visitor whenever he visits an ASTFnCallExprNode
        * @param node
        * Stores the address of the ASTFnCallExprNode to be visited
        */
        virtual void visit(ASTFnCallExprNode* node)=0;
    };
}


#endif //COMPILERSASSIGNMENT_VISITOR_H
