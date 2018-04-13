#include <iostream>
#include "Lexer/LexerImplementation.h"
#include "Parser/PredictiveParser.h"
#include "Visitors/XMLGenerator.h"

using namespace Lexer;
using namespace Parser;
using namespace Visitors;

/*
 * This is the main.cpp file and is used to call the compiler.
 * @return
 * 0 if correct execution , some error if no correct execution.
 */


int main() {
    PredictiveParser *parser = new PredictiveParser(
            new LexerImplementation(R"(C:\Users\Dylan Galea\ClionProjects\CompilersAssignment\Lexer\SourceCodeInput)"));
    XMLGenerator xml = XMLGenerator();
    xml.visitTree(parser->parse());
    delete(parser);
    return 0;
}