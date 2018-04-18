//
// Created by Dylan Galea on 17/04/2018.
//
/**
 * This class is used to create an interpreter execution pass , this class is a child of Visitor , thus it must implement
 * all the virtual methods in the interface class. The purpose of this class is so that the parse tree created by the predictive
 * parser , is used so that the program can be executed . Note that this class was implemented in a way such that first the program
 * is checked if it is valid or not , since if it is not valid , then the program cannot be evaluated . Also this made it
 * easier to focus more on the evaluation , rather than focusing on reporting errors,since this has already been done.
 */
#ifndef COMPILERSASSIGNMENT_INTERPRETEREXECUTIONPASS_H
#define COMPILERSASSIGNMENT_INTERPRETEREXECUTIONPASS_H

#include "Visitor.h"
#include "SemanticAnalysis.h"
#include <queue>

namespace Visitors{
    class InterpreterExecutionPass : Visitors::Visitor {
    private:
        SemanticAnalysis* validator; //This is used as to check whether the inputted program is valid , if not then
                                     // there is no use for executing the program.
        vector<SymbolTable*> ScopedTable; //this vector is used as to store the different scopes the program is in, whenever
                                          // a block is met a new scope is added at the end of the vector , then whenever
                                          // that block is ready , the last element from the vector is popped.
        vector<int> integerVals; // This vector is used to store the integer value that is currently being evaluated ,
                                 // one vector could have been used for all types to be more efficient , however this is easier
        vector<string> stringVals;//This vector is used to store the string value that is currently being evaluated
        vector<bool> boolVals; // This vector is used to store the bool value that is currently being evaluated
        vector<double> realVals; //This vector is used to store the real value that is currently being evaluated.
        bool returnStatementExecuted; // This boolean variable is used to indicate that a return statement has been executed
                                      // this is needed since , at a return the remaining statements must not be evaluated.
        bool inIfstatement; // this boolean variable is used to indicate that we are in an if statement , thus a return
                            // in the if statement pops the current scope and does not execute further statements in that scope
        bool inWhileStatement;// this boolean variable is used to indicate that we are in while statement , thus a return
                              // in the while statement pops the current scope and does not execute further statements in that scope
        Type lastEvaluatedType; // This field is used to identify the type of the last expression that has been evaluated
                                // so that the value can be pushed on the correct vector.
        FormalParams* functionParameters; // This field is used to store the formal parameters , to be added to the scope
        queue<TypeBinder::valueInIdentifier*> queueOfParams ; // This queue is used to add the value of the parameters ,
        // so that when the scope is opened , these parameters values are stored in the mapped value of the hash map ..i.e
        // the mapped TypeBinder instance.
    public:
        /**
         * This constructor is used to create a new InterpreterExecutionPass object instance , initializing all the
         * fields to default values , and give memory to the queue and vectors.
         */
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
