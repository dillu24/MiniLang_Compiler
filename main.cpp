#include <iostream>
#include "Lexer/LexerImplementation.h"
#include "Parser/PredictiveParser.h"

using namespace Lexer;
using namespace Parser;

/*
 * This is the main.cpp file and is used to call the compiler.
 * @return
 * 0 if correct execution , some error if no correct execution.
 */


int main() {
    PredictiveParser *parser = new PredictiveParser(
            new LexerImplementation(R"(C:\Users\Dylan Galea\ClionProjects\CompilersAssignment\Lexer\SourceCodeInput)"));
    parser->parse();
    /*Token *nextToken;
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
    delete(lexer);*/
    delete(parser);

    return 0;
}