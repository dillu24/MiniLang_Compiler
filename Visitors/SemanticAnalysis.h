//
// Created by Dylan Galea on 14/04/2018.
//

/**
 * This class is used to semantically analyze the inputted program. Thus it checks that the inputted valid statements
 * by the programmer make sense .
 */

#ifndef COMPILERSASSIGNMENT_SEMANTICANALYSIS_H
#define COMPILERSASSIGNMENT_SEMANTICANALYSIS_H

#include "Visitor.h"
#include "Utilities/SymbolTable.h"
#include <vector>
using namespace std;

namespace Visitors{
    class SemanticAnalysis:public Visitor {
    private:
        vector<SymbolTable*> ScopedTable; //Stores a scoped symbol table , where whenever a new block is met a new scope is
                                          //added , whenever a scope is closed , the last scope table in the vector will
                                          // be popped
        Type typeToBeChecked; //This stores the type of the expression that has been last evaluated so that it is matched
                              // for semantic type checking
        FormalParams* functionParameters;// this is used whenever a function is declared so that whenever a block is met
                                         // the function parameters are added to the next new scope .
        bool isReturnPresent = false; //this method is used to check if a return statement is present in a function
        Type returnType = Type::BOOL; //this method is used to check if the return statements are according to the signature of the function.
    public:
        /**
         * This constructor is used to create a new semantic analysis instance with an empty scope of symbol tables.
         */
        SemanticAnalysis();
        /**
         * This destructor is used to remove the global scope , had to be done this way due to the repl.
         */
        ~SemanticAnalysis();
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

        /**
         * This method is used to return the private symbol table
         * @return
         * The vector of type SymbolTable pointer , that contains the scoped symbol table instance
         */
        vector<SymbolTable*> getScopedTable();
    };
}

#endif //COMPILERSASSIGNMENT_SEMANTICANALYSIS_H
