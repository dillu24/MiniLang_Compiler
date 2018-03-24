#include <iostream>
#include "Lexer/LexerImplementation.h"

using namespace Lexer;

/*
 * This is the main.cpp file and is used to call the compiler.
 * @return
 * 0 if correct execution , some error if no correct execution.
 */


int main() {
    Token *nextToken;
    LexerImplementation *lexer = new LexerImplementation(
            R"(C:\Users\Dylan Galea\ClionProjects\CompilersAssignment\Lexer\SourceCodeInput)");
    while(true){
        nextToken = lexer->getNextToken();
        //cout<<nextToken->getTokenName();
        nextToken->printToken();
        cout<<" ";
        if(nextToken->getTokenType() == Token::TOK_EOF || nextToken->getTokenType() == Token::TOK_INVALID){
            break;
        }
    }
    delete(lexer);
    return 0;
}