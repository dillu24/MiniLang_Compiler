//
// Created by Dylan Galea on 14/03/2018.
//

#ifndef COMPILERSASSIGNMENT_TOKEN_H
#define COMPILERSASSIGNMENT_TOKEN_H

#include <iostream>
#include "State.h"


using namespace std;

namespace Lexer{
    class Token {
    public:
        enum TokenType{
            TOK_NUMBER,
            TOK_ARITHMETIC_OPERATOR,
            TOK_MINUS,
            TOK_EOF,
            TOK_PUNCTUATION,
            TOK_EQUALS,
            TOK_RELATIONAL_OPERATOR,
            TOK_STRING_LITERAL,
            TOK_IDENTIFIER,
            TOK_KEYWORD,
            TOK_INVALID
        };
        Token();
        Token(string lexeme,State state);
        ~Token();
        int getTokenValue();
        string getTokenName();
        TokenType getTokenType();
        char getTokenCharacterValue();
        string getTokenStringValue();
        void printToken();
    private:
        TokenType token_type;
        string token_name;
        int token_value;
        char token_character_value;
        string token_string_value;
        void determineTokenValues(string lexeme,State state);
        void setNumberToken(string lexeme);
        void setEOFToken();
        void setBinaryOperatorToken(string lexeme);
        void setPunctuationToken(string lexeme);
        void setEqualsToken();
        void setRelationalOperatorToken(string lexeme);
        void setStringLiteralToken(string lexeme);
        void setIdentifierToken(string lexeme);
        void setKeywordToken(string lexeme);
        void setMinusToken();
    };
}


#endif //COMPILERSASSIGNMENT_TOKEN_H
