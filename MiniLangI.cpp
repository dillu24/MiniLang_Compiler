#include <iostream>
#include "Lexer/LexerImplementation.h"
#include "Parser/PredictiveParser.h"
#include "Visitors/XMLGenerator.h"
#include "Visitors/InterpreterExecutionPass.h"
#include "Exceptions/CompilingErrorException.h"

using namespace Lexer;
using namespace Parser;
using namespace Visitors;
using namespace Exception;

/**
 * This is the main.cpp file and is used to call the compiler.
 * @return
 * 0 if correct execution , some error if no correct execution.
 */


int main() {
    try{
        PredictiveParser *parser = new PredictiveParser(
                new LexerImplementation(R"(C:\Users\Dylan Galea\ClionProjects\CompilersAssignment\Lexer\SourceCodeInput)"));
        auto * interpreter = new InterpreterExecutionPass();
        interpreter->visitTree(parser->parse());
        delete(parser);
    }catch(CompilingErrorException &e){
        cout<<e.getErrorMessage()<<endl;
    }
    return 0;
}