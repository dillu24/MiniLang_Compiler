//
// Created by Dylan Galea on 14/03/2018.
//

//TODO Ask about for and while
//ToDo - logic not
//ToDo Comments both multi line and single line
#include "LexerImplementation.h"
#include "Keywords.h"

#include <utility>
#include <stack>

Lexer::LexerImplementation::LexerImplementation() {
    initialize_input_characters("SourceCodeInput.txt");
    current_state = State::S0;
    current_input_index =0;
    lineNumber = 1;
}

Lexer::LexerImplementation::LexerImplementation(string file_name) {
    initialize_input_characters(std::move(file_name));
    current_state = State::S0;
    current_input_index =0;
    lineNumber = 1;
}

Lexer::LexerImplementation::~LexerImplementation() = default;

void Lexer::LexerImplementation::initialize_input_characters(string file_name) {
    fstream input_file;
    input_file.open(file_name);
    if(input_file.is_open()){
        cout<<"File opened"<<endl;
        char nextChar;
        while(input_file.get(nextChar)){
            input_characters.push_back(nextChar);
        }
        input_characters.push_back(EOF);
        input_file.close();
    }else{
        cout<<"File could not be opened"<<endl;
        input_file.close();
        exit(-1);
    }
}

Lexer::Token* Lexer::LexerImplementation::getNextToken() {
    current_state = State::S0;
    string lexeme;
    stack<State> stack;
    stack.push(State::BAD);
    while(current_state != State::SE){
        char next_character = input_characters[current_input_index];
        current_input_index++;
        if(lexeme.length()==0){ //to handle spaces when a token has been read , note that this was done this way
                                // in order not to interfere with white spaces in string literals
            if(next_character == ' '){
                continue;
            }else if(next_character =='\n'){
                lineNumber++;
                continue;
            }
        }
        if(next_character == '/'){ //handling of comments
            bool invalidComment = false;
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
        lexeme += next_character;
        current_state = transitionFunction(current_state,next_character);
        if(checkIfFinalState()){
            stack.empty();
        }
        stack.push(current_state);
    }
    while(!checkIfFinalState() && current_state != State::BAD){
        stack.pop();
        lexeme.pop_back();
        current_state = stack.top();
        current_input_index--; //to start from where last was accepted.
    }
    if(checkIfFinalState()){
        Token *token = new Token(lexeme,current_state);
        return token;
    }else{
        auto *token = new Token();
        cout<<"Syntax error in line "<<lineNumber<<endl;
        return token;
    }
}

bool Lexer::LexerImplementation::checkIfFinalState() {
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



