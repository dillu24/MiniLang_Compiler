//
// Created by Dylan Galea on 04/04/2018.
//

#include "PredictiveParser.h"
#include "../Lexer/Token.h"

Parser::PredictiveParser::PredictiveParser(LexerImplementation *lex) {
    lexer = &*lex;
    currentToken = new Token();
    nextToken = new Token();
    tree = new vector<AST::ASTNode*>();
}

Parser::PredictiveParser::~PredictiveParser() {
    delete nextToken;
    delete currentToken;
    delete lexer;
    for (auto &i : *tree) {
        delete i;
    }
    delete tree;
}

vector<ASTNode *>* Parser::PredictiveParser::parse() {
    while((nextToken=lexer->getNextToken())->getTokenType() != currentToken->TOK_EOF){
        lookAhead();
    }
    return tree;
}

void Parser::PredictiveParser::lookAhead() {
    currentToken = nextToken;
    nextToken = lexer->getNextToken();
}

