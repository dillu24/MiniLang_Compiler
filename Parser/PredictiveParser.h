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
    public :
        explicit PredictiveParser(LexerImplementation *lex);
        ~PredictiveParser();
        vector<ASTNode*>* parse();
        ASTStatementNode* parseStatement();
        ASTVarDeclStatementNode* parseVarDecl();
        ASTIdentifierExprNode* parseIdentifier();
    };
}


#endif //COMPILERSASSIGNMENT_PREDICTIVEPARSER_H
