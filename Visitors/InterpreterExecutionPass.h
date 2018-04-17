//
// Created by Dylan Galea on 17/04/2018.
//

#ifndef COMPILERSASSIGNMENT_INTERPRETEREXECUTIONPASS_H
#define COMPILERSASSIGNMENT_INTERPRETEREXECUTIONPASS_H

#include "Visitor.h"
#include "SemanticAnalysis.h"

namespace Visitors{
    class InterpreterExecutionPass : Visitors::Visitor {
    private:
        SemanticAnalysis* validator;
        vector<SymbolTable*> ScopedTable;
        vector<int> integerVals;
        vector<string> stringVals;
        vector<bool> boolVals;
        vector<double> realVals;
        bool returnStatementExecuted;
        Type lastEvaluatedType;
        FormalParams* functionParameters;
    public:
        InterpreterExecutionPass();
        /**
         * This method is the implementation of the virtual method in the base class
         * @param node
         * Stores the address of the ASTAssignStatementNode to be visited
         */
        void visit(ASTAssignStatementNode *node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTBlockStatementNode to be visited
        */
        void visit(ASTBlockStatementNode *node) override ;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTIfStatementNode to be visited
        */
        void visit(ASTIfStatementNode *node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTPrintStatementNode to be visited
        */
        void visit(ASTPrintStatementNode *node)override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTVarDeclStatementNode to be visited
        */
        void visit(ASTVarDeclStatementNode *node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTWhileStatementNode to be visited
        */
        void visit(ASTWhileStatementNode *node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTReturnStatement to be visited
        */
        void visit(ASTReturnStatementNode *node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTFuncDeclStatementNode to be visited
        */
        void visit(ASTFuncDeclStatementNode *node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTBinaryExpr to be visited
        */
        void visit(ASTBinaryExprNode *node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTNumberExprNode to be visited
        */
        void visit(ASTNumberExprNode* node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTBooleanLiteralExpressionNode to be visited
        */
        void visit(ASTBooleanLiteralExpressionNode* node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTStringLiteralExpr to be visited
        */
        void visit(ASTStringLiteralExprNode* node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTIdentifierExprNode to be visited
        */
        void visit(ASTIdentifierExprNode* node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTSubExprNode to be visited
        */
        void visit(ASTSubExprNode* node) override;
        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTUnaryExprNode to be visited
        */
        void visit(ASTUnaryExprNode* node) override;

        /**
        * This method is the implementation of the virtual method in the base class
        * @param node
        * Stores the address of the ASTFnCallExprNode to be visited
        */
        void visit(ASTFnCallExprNode* node) override;

        /**
        * This method is used by the visitor in order to start visiting the AST
        * @param tree
        * Stores the address of the AST to be visited.
        */
        void visitTree(vector<ASTStatementNode*>* tree) override;
    };
}

#endif //COMPILERSASSIGNMENT_INTERPRETEREXECUTIONPASS_H
