//
// Created by Dylan Galea on 14/04/2018.
//

#ifndef COMPILERSASSIGNMENT_SEMANTICANALYSIS_H
#define COMPILERSASSIGNMENT_SEMANTICANALYSIS_H

#include "Visitor.h"
#include "Types/SymbolTable.h"
#include <vector>
using namespace std;

namespace Visitors{
    class SemanticAnalysis:public Visitor {
    private:
        vector<SymbolTable*> ScopedTable;
        Type typeToBeChecked;
        FormalParams* functionParameters;
    public:
        /**
         * This constructor is used to create a new semantic analysis instance with an empty scope of symbol tables.
         */
        SemanticAnalysis();
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

#endif //COMPILERSASSIGNMENT_SEMANTICANALYSIS_H
