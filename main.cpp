#include <iostream>
#include "Lexer/LexerImplementation.h"

using namespace Lexer;


int main() {
    Token *nextToken;
    LexerImplementation *lexer = new LexerImplementation(
            R"(C:\Users\Dylan Galea\ClionProjects\CompilersAssignment\Lexer\SourceCodeInput)");
    while(true){
        nextToken = lexer->getNextToken();
        cout<<nextToken->getTokenName();
        //nextToken->printToken();
        cout<<" ";
        if(nextToken->getTokenType() == Token::TOK_EOF || nextToken->getTokenType() == Token::TOK_INVALID){
            break;
        }
    }
    delete(lexer);
    return 0;
}