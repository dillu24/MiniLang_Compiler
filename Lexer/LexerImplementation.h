//
// Created by Dylan Galea on 14/03/2018.
//

#ifndef COMPILERSASSIGNMENT_LEXER_H
#define COMPILERSASSIGNMENT_LEXER_H

#include <iostream>
#include <fstream>
#include <vector>
#include "Token.h"
#include "State.h"

using namespace std;


namespace Lexer{
    class LexerImplementation {
    public:
        LexerImplementation();
        LexerImplementation(string file_name);
        ~LexerImplementation();
        Token* getNextToken();
    private:
        int lineNumber;
        vector<char> input_characters;
        int current_input_index;
        void initialize_input_characters(string file_name);
        State current_state;
        State transitionFunction(State state,char input);
        bool checkIfFinalState();
        bool isBinaryOperator(char c);
        bool isPunct(char c);
    };
}



#endif //COMPILERSASSIGNMENT_LEXER_H
