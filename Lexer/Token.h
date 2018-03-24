//
// Created by Dylan Galea on 14/03/2018.
//

#ifndef COMPILERSASSIGNMENT_TOKEN_H
#define COMPILERSASSIGNMENT_TOKEN_H

#include <iostream>
#include "State.h"

/**
 * This class is used to encode a Token in our lexer , each token can be of the type TokenType enum , where then
 * depending on the final state , the token is initialized to one of the types accordingly. Note that the token
 * stores extra data , for example for a TOK_NUMBER we do not need the string , but for other token types we need. Thus
 * in the Token.cpp file whenever this data is not needed , this is set to -1.
 */


using namespace std;

namespace Lexer{
    class Token {
    public:
        /**
         * This type encodes the different types of tokens in our implementation , note that many of the types
         * were encoded into 1, for example the TOK_NUMBER is a token type that encodes numbers where then
         * additional information is needed in order to determine which number type (real or integer) it is referring
         * to.
         */
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
        /**
         * This is the default constructor , whenever this is used the token is initialized to invalid , i.e something
         * has gone wrong in the program
         */
        Token();
        /**
         * This constructor is used to initialize a token according to the lexeme and state it finsihed in
         * @param lexeme
         * Stores the lexeme that was scanned
         * @param state
         * Stores the state the scanning has ended on
         */
        Token(string lexeme,State state);
        ~Token(); //default destructor

        /**
         * This is a getter method used to get the token value , i.e whenever we have a token of type number this gets
         * it's value.
         * @return
         * An integer that refers to the value of the TOK_NUMBER
         */
        int getTokenValue();

        /**
         * This is a getter method used to get a name assigned to each token type in order to be more specific
         * @return
         * A string which represent more specifically the token we are representing
         */
        string getTokenName();
        /**
         * This gets the token type of the token , i.e one of the values in the enum TokenType
         * @return
         * A TokenType value that represents the type of the token
         */
        TokenType getTokenType();
        /**
         * This is a getter method and is used to get the character value representing a token , for example if the
         * token is TOK_ARITHMETIC_OPERATOR and the lexeme is plus "+" this method gets '+'.
         * @return
         * The token character representation
         */
        char getTokenCharacterValue();
        /**
         * This method gets the string representation of the lexeme representing the token
         * @return
         * Returns the string representation of the lexeme representing the token
         */
        string getTokenStringValue();
        /**
         * This method is used for convention to print the string representing each token , i.e it prints back
         * the inputted lexeme in order to check for testing that the programm was correctly scanned
         */
        void printToken();
    private:
        TokenType token_type; //stores the token type
        string token_name; //stores a specific token name related to the token type
        int token_value; // stores the integer representing the lexeme that is related to the token
        char token_character_value; // stores the character representing the lexeme that is related to the token
        string token_string_value; // stores the string representing the lexeme that is related to the token
        /**
         * This method is used to initialize the token depending on the lexeme that was scanned , and on which
         * state the lexer ended .
         * @param lexeme
         * Stores the lexeme that has been scanned
         * @param state
         * Stores the state the lexer ended on
         */
        void determineTokenValues(string lexeme,State state);
        /**
         * This method is used to set a number token depending on the lexeme that has been scanned
         * @param lexeme
         * The lexeme that has been scanned
         */
        void setNumberToken(string lexeme);
        /**
         * This method is used to set an EOF TOKEN
         */
        void setEOFToken();
        /**
         * This method is used to set a binary operator token depending on the lexeme that has been scanned
         * @param lexeme
         * The lexeme that has been scanned
         */
        void setBinaryOperatorToken(string lexeme);
        /**
         * This method is used to set a punctuation token depending on the lexeme that has been scanned
         * @param lexeme
         * The lexeme that has been scanned
         */
        void setPunctuationToken(string lexeme);
        /**
         * This method is used to set and equals token. This was seperated from other relational operators in order
         * to be more concise with the DFSA.
         */
        void setEqualsToken();
        /**
         * This method is used to set a relational operator token depending on the lexeme that has been scanned
         * @param lexeme
         * The lexeme that has been scanned
         */
        void setRelationalOperatorToken(string lexeme);
        /**
         * This method is used to set a Sting Literal token depending on the lexeme that has been scanned
         * @param lexeme
         * The lexeme that has been scanned
         */
        void setStringLiteralToken(string lexeme);
        /**
         * This method is used to set an identified token depending on the lexeme that has been scanned
         * @param lexeme
         * The lexeme that has been scanned
         */
        void setIdentifierToken(string lexeme);
        /**
         * This method is used to set a keyword token depending on the lexeme that has been scanned
         * @param lexeme
         * The lexeme that has been scanned
         */
        void setKeywordToken(string lexeme);

        /**
         * This method is used to set a minus token depending on the lexeme that has been scanned , note this
         * was sepearated from the operator tokens because in the language the minus can represent a negation
         * to an expression.
         */
        void setMinusToken();
    };
}


#endif //COMPILERSASSIGNMENT_TOKEN_H
