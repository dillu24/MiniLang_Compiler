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

void help(){
    cout<<"Any of the following commands makes the Interpreter act :"<<endl;
    cout<<"1.MiniLang commands to be executed"<<endl;
    cout<<"2.Enter #st to display symbol table"<<endl;
    cout<<"3.Enter #help for help"<<endl;
    cout<<"4.Enter #exit to exit interpreter"<<endl;
    cout<<"5.Enter #load to load a text file. NOTE TEXT FILE MUST BE IN CompilersAssignment/Lexer"<<endl;
    cout<<"6.Any command that does not fit the above will be declared as invalid"<<endl;
    cout<<"7.Note white spaces and empty statements are ignored , so you have to enter something"<<endl;
}

int main() {
    auto * lexer = new LexerImplementation();
    auto* parser = new PredictiveParser(lexer);
    auto* interpreterExecutor = new InterpreterExecutionPass();
    cout<<"Minilang Interpreter running ,enter #help for command breakdown"<<endl;
    cout<<"MLI> ";
    string input;
    getline(cin,input);
    double ans;
    //ToDo .. problem in getting next token in parser or lexer .. ma nafx ghad fejni l problema .. lewwel statement ok mbad fuck up
    while(true){
        try{
            if(input == "#help"){
                help();
            }else if(input == "#st"){

            }else if(input == "#load"){

            }else if(input == "#exit"){
                break;
            }else{
                lexer->initializeCharactersWithString(input);
                interpreterExecutor->visitTree(parser->parse());
                lexer->clearCharactersContainer();
            }
        }catch(CompilingErrorException &e){
            cout<<e.getErrorMessage()<<endl;
        }
        cout<<"MLI> ";
        getline(cin,input);
    }
    cout<<"Bye :)"<<endl;
    delete(interpreterExecutor,parser,lexer);
    return 0;
}