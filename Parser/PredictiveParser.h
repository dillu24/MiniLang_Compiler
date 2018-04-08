//
// Created by Dylan Galea on 04/04/2018.
//

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

using namespace Lexer;
using namespace AST;

namespace Parser{
    class PredictiveParser {
    private:
        LexerImplementation *lexer;
        Token *currentToken;
        Token *nextToken;
        vector<ASTNode*> *tree;
        void lookAhead();
        ASTExprNode* parseStatement();
        ASTLiteralExprNode * parseLiteral();
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
    public :
        explicit PredictiveParser(LexerImplementation *lex);
        ~PredictiveParser();
        vector<ASTNode*>* parse();
    };
}


#endif //COMPILERSASSIGNMENT_PREDICTIVEPARSER_H
