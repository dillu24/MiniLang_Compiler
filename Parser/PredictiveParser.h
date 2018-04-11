//
// Created by Dylan Galea on 04/04/2018.
//

/**
 * This class is used to implement the Recursive Descendt Predictive parser , each EBNF non terminal thus must be parsed
 * and a parse method is created for each ,in order to create the respective nodes.
 */

#ifndef COMPILERSASSIGNMENT_PREDICTIVEPARSER_H
#define COMPILERSASSIGNMENT_PREDICTIVEPARSER_H

#include "../Lexer/LexerImplementation.h"
#include "../ASTHierarchy/ASTNode.h"
#include "../ASTHierarchy/ASTStatementNode.h"
#include "../ASTHierarchy/Expression/ASTNumberExprNode.h"
#include "../ASTHierarchy/Statement/ASTPrintStatementNode.h"
#include "../ASTHierarchy/Statement/ASTVarDeclStatementNode.h"
#include "../ASTHierarchy/Operators.h"
#include "../ASTHierarchy/Expression/ASTFnCallExprNode.h"
#include "../ASTHierarchy/Expression/ASTSubExprNode.h"
#include "../ASTHierarchy/Expression/ASTUnaryExprNode.h"
#include "../ASTHierarchy/Statement/ASTAssignStatementNode.h"
#include "../ASTHierarchy/Statement/ASTReturnStatementNode.h"
#include "../ASTHierarchy/Statement/ASTBlockStatementNode.h"
#include "../ASTHierarchy/Statement/ASTIfStatementNode.h"
#include "../ASTHierarchy/Statement/ASTWhileStatementNode.h"
#include "../ASTHierarchy/Statement/FormalParam.h"
#include "../ASTHierarchy/Statement/FormalParams.h"
#include "../ASTHierarchy/Statement/ASTFuncDeclStatementNode.h"

using namespace Lexer;
using namespace AST;

namespace Parser{
    class PredictiveParser {
    private:
        LexerImplementation *lexer; // Stores the address of the Lexer
        Token *currentToken; // Stores the address of the current token being parsed
        Token *nextToken; // stores the address of the next token to be parsed.
        vector<ASTStatementNode*> *tree; //stores the AST that was outputted from the list of tokens .. the root node is the vector pointer itself
                                         // where the content is the different branches
        /**
         * This method is used to switch the value of this->currentToken to this->nextToken , and the value of this->nextToken
         * is assigned to the value returned by the Lexer::getNextToken() method in order to parse more tokens.
         */
        void lookAhead();
        /**
         * This method is used to parse a statement according to the EBND given in the specification sheet
         * @return
         * An ASTStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only. Note each statement has a branch in the AST.
         */
        ASTStatementNode* parseStatement();
        /**
         * This method is used to parse a literal according to the EBNF given in the specification sheet
         * @return
         * An ASTLiteralExprNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTLiteralExprNode * parseLiteral();
        /**
         * This method is used to parse a variable declaration according to the EBNF given in the specification sheet
         * @return
         * An ASTVarDeclStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTVarDeclStatementNode* parseVarDecl();
        ASTIdentifierExprNode* parseIdentifier();
        ASTExprNode* parseExpression();
        ASTExprNode* parseSimpleExpr();
        Operators parseOperator();
        Type parseType();
        ASTFnCallExprNode* parseFnCall();
        vector<ASTExprNode*>* parseActualParams();
        ASTSubExprNode* parseSubExpr();
        ASTUnaryExprNode* parseUnary();
        NegationOperator parseNegOp();
        ASTExprNode* parseFactor();
        ASTExprNode* parseTerm();
        ASTAssignStatementNode* parseAssignStatement();
        ASTPrintStatementNode* parsePrintStatement();
        ASTReturnStatementNode* parseReturnStatement();
        ASTBlockStatementNode* parseBlockStatement();
        ASTIfStatementNode* parseIfStatement();
        ASTWhileStatementNode* parseWhileStatement();
        FormalParam* parseFormalParam();
        FormalParams* parseFormalParams();
        ASTFuncDeclStatementNode* parseFunctionDefinition();
    public :
        explicit PredictiveParser(LexerImplementation *lex);
        ~PredictiveParser();
        vector<ASTStatementNode*>* parse();
    };
}


#endif //COMPILERSASSIGNMENT_PREDICTIVEPARSER_H
