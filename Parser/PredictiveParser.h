//
// Created by Dylan Galea on 04/04/2018.
//

#ifndef COMPILERSASSIGNMENT_PREDICTIVEPARSER_H
#define COMPILERSASSIGNMENT_PREDICTIVEPARSER_H

#include "../Lexer/LexerImplementation.h"
#include "../ASTHierarchy/ASTNode.h"

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
    };
}


#endif //COMPILERSASSIGNMENT_PREDICTIVEPARSER_H
