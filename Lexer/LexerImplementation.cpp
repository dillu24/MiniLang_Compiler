//
// Created by Dylan Galea on 14/03/2018.
//

#include "LexerImplementation.h"
#include "Keywords.h"
#include "../Exceptions/CompilingErrorException.h"

#include <utility>
#include <stack>
using namespace Exception;

Lexer::LexerImplementation::LexerImplementation() {
    current_state = State::S0; //initialize start state
    current_input_index =0; //initialize current state in the source program
    lineNumber = 1; // started from line 1
}

Lexer::LexerImplementation::LexerImplementation(string file_name) {
    initialize_input_characters(std::move(file_name)); //get source file and initialzie input character
    current_state = State::S0; //initialize start state
    current_input_index =0; // initialize current state in the source program
    lineNumber = 1; // start from line 1
}

Lexer::LexerImplementation::~LexerImplementation() = default;

void Lexer::LexerImplementation::initialize_input_characters(string file_name) {
    fstream input_file;
    input_file.open(file_name);
    if(input_file.is_open()){
        char nextChar;
        while(input_file.get(nextChar)){ //until end of file keep reading characters and save them
            input_characters.push_back(nextChar);
        }
        input_characters.push_back(EOF); // push EOF marker as an indication that reading of characters is done
        input_file.close(); //close file
    }else{
        input_file.close();
        throw CompilingErrorException("Source file could not be opened"); // throw exception with corresponding error message
    }
}

Lexer::Token* Lexer::LexerImplementation::getNextToken() {
    current_state = State::S0; // start from start state
    string lexeme; // lexeme that is read so far
    stack<State> stack; // stack to store the states
    stack.push(State::BAD); // push bad state in order to check for valid input
    while(current_state != State::SE){
        char next_character = input_characters[current_input_index]; // read next character from source file
        current_input_index++; // go to the next character for next iteration
        if(lexeme.length()==0){ //to handle spaces when a token has been read , note that this was done this way
                                // in order not to interfere with white spaces in string literals
            if(next_character == ' ' || next_character == '\t'){ // if next is a space skip the character since it is not in a string literal,
                                       // if it where in a string literal the lexeme length would be greater than zero
                                       // since the first character is ""
                continue;
            }else if(next_character =='\n'){ // if new line has been encountered skip it also and increment the line
                                             // number for error reporting
                lineNumber++;
                continue;
            }
        }
        if(next_character == '/'){ //handling of comments
            bool invalidComment = false; // in order to check for invalid coments
            if(input_characters[current_input_index] == '/'){ //if next character is a forward slash this means a comment
                                                              // should be interpreted
                while (input_characters[current_input_index] != '\n' && input_characters[current_input_index] != EOF){
                    current_input_index++;//move until we find the breaking point of the line comment
                }
                continue;
            }else if(input_characters[current_input_index] == '*'){ // if we have a block comment
                int originalIndex = current_input_index; //store the current index to continue from this in case the comment is
                                                         // not closed correctly , so that tokens can be outputted
                int originalLineNumber = lineNumber;
                while(true){
                    current_input_index++;
                    if(input_characters[current_input_index]=='\n'){
                        lineNumber++;
                    }
                    if(input_characters[current_input_index] == '*' && input_characters[current_input_index+1] == '/'){
                        current_input_index +=2; //if we found it's closing move to the next uncommented character
                        break;
                    }
                    if(input_characters[current_input_index] == EOF){ // if we did not find a closing
                        invalidComment = true; // we have an inalid comment
                        current_input_index = originalIndex; // hence we need to commence reading tokens from the start
                                                             // of the opening token , thus the parser would notice the
                                                             // bad logic
                        lineNumber = originalLineNumber; //since have to skip when meeting comments.
                        break;
                    }
                }
                if(!invalidComment){ // if we have a valid comment we must continue to read from the next uncommented char
                    continue;
                }
            }
        }
        lexeme += next_character; // if no comments , spaces , new lines are present add character to lexeme
        current_state = transitionFunction(current_state,next_character); // get next state
        if(checkIfFinalState()){ // if this is final state no need to store previous states.
            while(!stack.empty()){
               stack.pop();
            }
        }
        stack.push(current_state); //push current state
    }
    while(!checkIfFinalState() && current_state != State::BAD){ // get ending state and lexeme depending on that ending
        stack.pop();
        lexeme.pop_back();
        current_state = stack.top();
        current_input_index--; //to start from where last was accepted.
    }
    if(checkIfFinalState()){ //check if ending state is final
        Token *token = new Token(lexeme,current_state); // if final a valid token is initialized
        return token;
    }else{ // otherwise we get an invalid token , therefore terminate lexer
        throw CompilingErrorException("syntax error in line "+to_string(lineNumber)); // throw exception with respective error message to signal error
    }
}

bool Lexer::LexerImplementation::checkIfFinalState() { // This method determines which are the final states according
                                                       // to the given DFSA
    switch(current_state){
        case State::S1:
        case State::S2:
        case State::S4:
        case State::S5:
        case State::S6:
        case State::S7:
        case State::S8:
        case State::S9:
        case State::S10:
        case State::S13:
        case State::S14:
        case State::S15:
            return true;
        default:
            return false;
    }
}

Lexer::State Lexer::LexerImplementation::transitionFunction(Lexer::State state, char input) {
    //The transition function , in order to understand fully see diagram
    switch(state){
        case State::S0:
            if(isdigit(input)){
                return State::S1;
            }else if (input == EOF){
                return State::S2;
            }else if(isBinaryOperator(input)) {
                return State::S5;
            }else if(isPunct(input)) {
                return State::S6;
            }else if(input == '=') {
                return State::S7;
            }else if(input == '>') {
                return State::S10;
            }else if(input == '<') {
                return State::S9;
            }else if(input == '!') {
                return State::S11;
            }else if(input == '"') {
                return State::S12;
            }else if(input == '_' || isalpha(input)) {
                return State::S14;
            }else if(input == '-'){
                return State::S15;
            }else{
                return State::SE;
            }
        case State::S1:
            if(isdigit(input)){
                return State::S1;
            }else if(input =='.'){
                return State ::S3;
            }else{
                return State ::SE;
            }
        case State::S3:
            if(isdigit(input)){
                return State::S4;
            }else{
                return State::SE;
            }
        case State::S4:
            if(isdigit(input)){
                return State::S4;
            }else{
                return State::SE;
            }
        case State::S10:
        case State::S7:
        case State::S9:
        case State::S11:
            if(input =='='){
                return State::S8;
            }else{
                return State::SE;
            }
        case State::S12:
            if(input == '"'){
                return State::S13;
            }else{
                return State::S12;
            }
        case State::S14:
            if(input == '_' || isalpha(input) || isdigit(input)){
                return State::S14;
            }else{
                return State::SE;
            }
        default:
            return State::SE;
    }

}

bool Lexer::LexerImplementation::isBinaryOperator(char c) {
    return c == '+' || c == '/' || c == '*';
}

bool Lexer::LexerImplementation::isPunct(char c) {
    return c == '{' || c == '}' || c == '(' || c == ')' || c == ',' || c == ';' || c == ':';
}

void Lexer::LexerImplementation::initializeCharactersWithString(string input) {
    for (char i : input) {
        input_characters.push_back(i);
    }
    input_characters.push_back(EOF);
}

void Lexer::LexerImplementation::clearCharactersContainer() {
    input_characters.clear();
}

void Lexer::LexerImplementation::restartCurrentInputIndex() {
    current_input_index = 0;
    lineNumber = 1;
}



