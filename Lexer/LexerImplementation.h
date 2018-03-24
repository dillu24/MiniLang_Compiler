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

/**
 * This class is used to implement the lexer and get the next token within the source code program.
 */

namespace Lexer{
    class LexerImplementation {
    public:
        /**
         * This constructor is used to initialize the lexer fields and set the current state to S0(the first state
         * in the DFSA) . Also it reads the default file SourceCodeInput , supplied in this directory.
         */
        LexerImplementation();
        /**
         * This constructor is used to initialize the lexer fields and set the current state to S0(the first state in
         * the DFSA) . However the different from the other constructor is that this reads from any file path supplied
         * in the file_name parameter
         * @param file_name
         * Stores the file path the lexer is to read from
         */
        LexerImplementation(string file_name);
        ~LexerImplementation(); //default destructer
        /**
         * This method is used to get the next token that the lexer has identified
         * @return
         * A pointer to the next token the lexer has identified
         */
        Token* getNextToken();
    private:
        int lineNumber; // This stores the line number the lexer is in , in order to report lexing errors
        vector<char> input_characters; // stores the characters identified in the input file
        int current_input_index; //stores the current index the lexer is in in order to read the next character
        /**
         * This method initialized the list of characters in the source input program supplied as parameter
         * @param file_name
         * Stores the path the lexer is to read from as input program
         */
        void initialize_input_characters(string file_name);
        State current_state; // Stores the current state in the DFSA the lexer is in
        /**
         * This is a function that determines the next state in the DFSA depending on the state the lexer is currently
         * in , and the input character the lexer has read . Note that we have implemented a table driven lexer , however
         * the table was not defined as an actual 2D array in order not to have 0(n^2) memory saved , however this was
         * implemented as a switch case statements
         * @param state
         * Stores the state the lexer is currently in
         * @param input
         * Stores the input character evaluated from the source program
         * @return
         * The next state to go to.
         */
        State transitionFunction(State state,char input);
        /**
         * This method check if the current state is a final state
         * @return
         * True if final state
         * False if no
         */
        bool checkIfFinalState();
        /**
         * This method checks if 'c' is a binary operator . Note that '-' in this language can be also a negation symbol
         * thus it was not considered in this method
         * @param c
         * The character to be evaluated
         * @return
         * True if Binary Operator
         * False if not a Binary Operator
         */
        bool isBinaryOperator(char c);

        /**
         * This method checks if 'c' is a punctuation symbol
         * @param c
         * The character to be evaluated
         * @return
         * True if punctutation symbol
         * False if not punctuation symbol
         */
        bool isPunct(char c);
    };
}



#endif //COMPILERSASSIGNMENT_LEXER_H
