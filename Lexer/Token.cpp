//
// Created by Dylan Galea on 14/03/2018.
//

#include "Token.h"
#include "Keywords.h"

#include <utility>

/**
 * This class implements the methods in the "Token.h" file
 */

Lexer::Token::Token(){ // default if no state and lexeme is found set the token as invalid
    token_type = TOK_INVALID;
    token_name = "INVALID TOKEN";
    token_value = -1;
    token_character_value = -1;
    token_string_value = "";
}

Lexer::Token::Token(string lexeme,State state) { // whenever a lexeme and state are passed determine the token
                                                 // in order to initialize it
    determineTokenValues(std::move(lexeme),state);
}

Lexer::Token::~Token() = default; //default destructor , nothing special to do when end of program

int Lexer::Token::getTokenValue() { //getter method for token_value
    return token_value;
}

string Lexer::Token::getTokenStringValue() { //getter method for token_string_value
    return token_string_value;
}

char Lexer::Token::getTokenCharacterValue() { //getter method for token_character_value
    return token_character_value;
}

string Lexer::Token::getTokenName() { //getter method for token_name
    return token_name;
}

Lexer::Token::TokenType Lexer::Token::getTokenType() { //getter method for token_type
    return token_type;
}

void Lexer::Token::determineTokenValues(string lexeme,State state) {
    switch(state){
        //This method takes the state the lexer ended on , if one of these states is ended upon then we got a valid
            // token and this must be initialized according to the DFSA.
        case State::S1:
        case State::S4:
            setNumberToken(std::move(lexeme));
            break;
        case State::S2:
            setEOFToken();
            break;
        case State::S5:
            setBinaryOperatorToken(std::move(lexeme));
            break;
        case State::S6:
            setPunctuationToken(std::move(lexeme));
            break;
        case State::S7:
            setEqualsToken();
            break;
        case State::S8:
        case State::S9:
        case State::S10:
            setRelationalOperatorToken(std::move(lexeme));
            break;
        case State::S13:
            setStringLiteralToken(lexeme);
            break;
        case State::S14:{
            auto *kw =new  Keywords();
            set <string>* languageKeyWords = kw->getKeywordsList();
            if(languageKeyWords->find(lexeme) != languageKeyWords->end()){ // if we find the lexeme as a keyword
                                                                           // set it as keyword token
                setKeywordToken(lexeme);
            }else{ // if this is not a keyword then it must be a word not within "" , thus it must be an identifier
                   // token
                setIdentifierToken(lexeme);
            }
            delete (kw);
            break;
        }
        case State::S15:
            setMinusToken();
            break;
        default: // if the lexer did not end in either of these states , then it must be an invalid input
            token_type = TOK_INVALID;
            token_name = "INVALID TOKEN";
            token_character_value =-1;
            token_value =-1;
            token_string_value = "";
    }
}

void Lexer::Token::setNumberToken(string lexeme) {
    token_type = TOK_NUMBER;
    token_value = stoi(lexeme);
    if(lexeme.find('.') != string::npos){ // if there is a full stop we have a real number
        token_name = "REAL NUMBER";
    }else{ // otherwise the number must be an integer
        token_name = "INTEGER NUMBER";
    }
    token_character_value = -1; // no need to store character value for a number
    token_string_value = lexeme;
}

void Lexer::Token::setEOFToken(){ //set EOF value accordingly
    token_type= TOK_EOF;
    token_name = "EOF TOKEN";
    token_value = -1; // no value to be stored
    token_character_value = EOF;
    token_string_value = "EOF";
}

void Lexer::Token::setBinaryOperatorToken(string lexeme) {
    token_type = TOK_ARITHMETIC_OPERATOR;
    token_name = "BINARY OPERATOR TOKEN";
    token_value = -1; // no value to be stored
    token_character_value = lexeme.at(0);
    token_string_value = lexeme;
}

void Lexer::Token::setPunctuationToken(string lexeme) {
    token_type = TOK_PUNCTUATION;
    token_value = -1; // novalue to be stored
    token_character_value = lexeme.at(0);
    if(lexeme.at(0)=='{'){ //give name according to lexeme
        token_name = "LEFT CURLY BRACKET TOKEN";
    }else if(lexeme.at(0)=='}'){
        token_name = "RIGHT CURLY BRACKET TOKEN";
    }else if(lexeme.at(0)=='('){
        token_name = "LEFT ROUND BRACKET TOKEN";
    }else if(lexeme.at(0)==')'){
        token_name = "RIGHT ROUND BRACKET TOKEN";
    }else if(lexeme.at(0)==';'){
        token_name = "SEMI COLON TOKEN";
    }else if(lexeme.at(0)==':'){
        token_name = "COLON TOKEN";
    }else if(lexeme.at(0)==','){
        token_name = "COMMA TOKEN";
    }
    token_string_value = lexeme;
}

void Lexer::Token::setEqualsToken() {
    token_type = TOK_EQUALS;
    token_name = "EQUALS TOKEN";
    token_value = -1; // no value to be stored
    token_character_value = '=';
    token_string_value = "=";
}

void Lexer::Token::setRelationalOperatorToken(string lexeme) {
    token_type = TOK_RELATIONAL_OPERATOR;
    token_value = -1; //no value to be stored
    if(lexeme == "<="){ //give value according to lexeme
        token_character_value = -1;
        token_name = "LESS OR EQUAL TOKEN";
    }else if(lexeme == ">="){
        token_character_value = -1;
        token_name = "GREATER OR EQUAL TOKEN";
    }else if(lexeme == ">"){
        token_character_value = '>';
        token_name = "GREATER THAN TOKEN";
    }else if(lexeme == "!="){
        token_character_value = -1;
        token_name = "NOT EQUAL TO TOKEN";
    }else if(lexeme== "=="){
        token_character_value = -1;
        token_name = "IS EQUAL TO TOKEN";
    }else if(lexeme == "<"){
        token_character_value = '<';
        token_name = "LESS THAN TOKEN";
    }
    token_string_value = lexeme;
}

void Lexer::Token::setStringLiteralToken(string lexeme) {
    token_string_value = std::move(lexeme);
    token_string_value.pop_back(); //to remove back ""
    token_string_value.erase(0,1); // to remove front ""
    token_type = TOK_STRING_LITERAL;
    token_name = "STRING LITERAL TOKEN";
    token_character_value = -1; // no value to be stored
    token_value = -1; // no value to be stored
}

void Lexer::Token::setIdentifierToken(string lexeme) {
    token_string_value = std::move(lexeme);
    token_type = TOK_IDENTIFIER;
    token_name = "IDENTIFIER TOKEN";
    token_character_value = -1; // no value to be stored
    token_value = -1; // no value to be stored
}

void Lexer::Token::setKeywordToken(string lexeme) {
    token_string_value = std::move(lexeme);
    token_type = TOK_KEYWORD;
    token_name = "KEYWORD TOKEN";
    token_character_value = -1; // no value to be stored
    token_value = -1; // no value to be stored
}

void Lexer::Token::printToken() {
    cout<<token_string_value;
}

void Lexer::Token::setMinusToken() {
    token_string_value = "-";
    token_type = TOK_MINUS;
    token_name = "MINUS TOKEN";
    token_character_value = '-';
    token_value = -1; // no value to be stored
}



