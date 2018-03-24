//
// Created by Dylan Galea on 14/03/2018.
//

#include "Token.h"
#include "Keywords.h"

#include <utility>

Lexer::Token::Token(){
    token_type = TOK_INVALID;
    token_name = "INVALID TOKEN";
    token_value = -1;
    token_character_value = -1;
    token_string_value = "";
}

Lexer::Token::Token(string lexeme,State state) {
    determineTokenValues(std::move(lexeme),state);
}

Lexer::Token::~Token() = default;

int Lexer::Token::getTokenValue() {
    return token_value;
}

string Lexer::Token::getTokenStringValue() {
    return token_string_value;
}

char Lexer::Token::getTokenCharacterValue() {
    return token_character_value;
}

string Lexer::Token::getTokenName() {
    return token_name;
}

Lexer::Token::TokenType Lexer::Token::getTokenType() {
    return token_type;
}

void Lexer::Token::determineTokenValues(string lexeme,State state) {
    switch(state){
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
            if(languageKeyWords->find(lexeme) != languageKeyWords->end()){
                setKeywordToken(lexeme);
            }else{
                setIdentifierToken(lexeme);
            }
            delete (kw);
            break;
        }
        case State::S15:
            setMinusToken();
            break;
        default:
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
    if(lexeme.find('.') != string::npos){
        token_name = "REAL NUMBER";
    }else{
        token_name = "INTEGER NUMBER";
    }
    token_character_value = -1;
    token_string_value = lexeme;
}

void Lexer::Token::setEOFToken(){
    token_type= TOK_EOF;
    token_name = "EOF TOKEN";
    token_value = -1;
    token_character_value = EOF;
    token_string_value = "EOF";
}

void Lexer::Token::setBinaryOperatorToken(string lexeme) {
    token_type = TOK_ARITHMETIC_OPERATOR;
    token_name = "BINARY OPERATOR TOKEN";
    token_value = -1;
    token_character_value = lexeme.at(0);
    token_string_value = lexeme;
}

void Lexer::Token::setPunctuationToken(string lexeme) {
    token_type = TOK_PUNCTUATION;
    token_value = -1;
    token_character_value = lexeme.at(0);
    if(lexeme.at(0)=='{'){
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
    token_value = -1;
    token_character_value = '=';
    token_string_value = "=";
}

void Lexer::Token::setRelationalOperatorToken(string lexeme) {
    token_type = TOK_RELATIONAL_OPERATOR;
    token_value = -1;
    if(lexeme == "<="){
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
    token_character_value = -1;
    token_value = -1;
}

void Lexer::Token::setIdentifierToken(string lexeme) {
    token_string_value = std::move(lexeme);
    token_type = TOK_IDENTIFIER;
    token_name = "IDENTIFIER TOKEN";
    token_character_value = -1;
    token_value = -1;
}

void Lexer::Token::setKeywordToken(string lexeme) {
    token_string_value = std::move(lexeme);
    token_type = TOK_KEYWORD;
    token_name = "KEYWORD TOKEN";
    token_character_value = -1;
    token_value = -1;
}

void Lexer::Token::printToken() {
    cout<<token_string_value;
}

void Lexer::Token::setMinusToken() {
    token_string_value = "-";
    token_type = TOK_MINUS;
    token_name = "MINUS TOKEN";
    token_character_value = '-';
    token_value = -1;
}



