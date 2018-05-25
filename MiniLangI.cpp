/**
 * This class encodes the REPL , where an instance of the lexer,parser and interpreter executor is kept. This main
 * method keeps on looping until the user enters #exit . Whenever the user enters #load , the program asks the user
 * for the text file he wants to input to the compiler ,it is important that the source code is in
 * CompilersAssignment/TestPrograms. Also if the user enters #st , the current state of the symbol table is displayed,
 * where the name of the identifier next to the nature of the identifier are displayed . If the user enters a valid
 * statement , that is tokenized , the parse tree is created for that statement , and the semantic analyzer and executor
 * are also run until an answer is display . It is important that the lexer restarts from the initial state and the
 * syntax tree is emptied , so that on the next statement we do not execute previously executed statements. Also ,
 * if the user wants to enter large programs he cannot enter them directly in the console , but load them from a text
 * file . This was done this was since it is more practable. Note the interpreter works in a way like the ebnf , for
 * example if 4+5 is entered , this is an invalid statement , since the ebnf specifies that a print ,etc.. must be
 * before it.
 */

#include <iostream>
#include "Lexer/LexerImplementation.h"
#include "Parser/PredictiveParser.h"
#include "Visitors/InterpreterExecutionPass.h"
#include "Exceptions/CompilingErrorException.h"
#include "Visitors/XMLGenerator.h"

using namespace Lexer;
using namespace Parser;
using namespace Visitors;
using namespace Exception;



/**
 * This method displays the help screen menu
 */
void help(){
    cout<<"Any of the following commands makes the Interpreter act :"<<endl;
    cout<<"1.MiniLang commands to be executed"<<endl;
    cout<<"2.Enter #st to display symbol table"<<endl;
    cout<<"3.Enter #help for help"<<endl;
    cout<<"4.Enter #exit to exit interpreter"<<endl;
    cout<<"5.Enter #load to load a text file. NOTE TEXT FILE MUST BE IN CompilersAssignment/TestPrograms"<<endl;
    cout<<"6.Any command that does not fit the above will be declared as invalid"<<endl;
    cout<<"7.Note white spaces and empty statements are ignored , so you have to enter something"<<endl;
}

int main() {
    auto * lexer = new LexerImplementation(); //instance of the lexer
    auto* parser = new PredictiveParser(lexer); // instance of the parser
    auto* xml = new XMLGenerator();
    auto* interpreterExecutor = new InterpreterExecutionPass(); // instance of the exectuor which contains the semantic analyzer also
    cout<<"Minilang Interpreter running ,enter #help for command breakdown"<<endl;
    cout<<"MLI> ";
    string input;
    SymbolTable tempValue ; // used in case when an exception is thrown whilst in a function block in the symbol table
    getline(cin,input); //get input
    vector<SymbolTable> scopedTemp = vector<SymbolTable>(); // used in case when an exception is thown whilst in a function block in symbol table
    while(true) { // keep iterating
        //Store previous state so that if an exception happens whilst the interpretetr is in a function block , the state
        // of the program prior to loading the program is kept , this had to be implemented because in the function
        //declaration in order to implement factorial , the function had to be inserted immediately in the symbol table
        //for semantics
        for(unsigned int i=0;i<interpreterExecutor->getValidator()->getScopedTable().size();i++){
            scopedTemp.push_back(*interpreterExecutor->getValidator()->getScopedTable().at(i));
        }
        try {
            if (input == "#help") { // if help is entered display help screen menu
                help();
            } else if (input == "#st") { // if st is entered
                vector<SymbolTable*> st = interpreterExecutor->getScopedTable();// get symbol table containingg values
                for (auto &i : st) {
                    auto contents = i->getMultimap(); // get the multimap corresponding to the current scope
                    int j = 0; // sort of index in the multimap
                    for (auto &content : contents) { // iterate untill the end of multimap
                        j++;
                        //display the name of the identifier and it's type(function or variable)
                        cout <<j<<"."<<content.first<<" "<<content.second.getStringRepresentationOfIdentifierType()<<
                             " "<<content.second.getStringRepresentationOfPrimitiveType();
                        if(content.second.getStringRepresentationOfIdentifierType()=="variable"){ //display value if variable , according to it's type
                            if(content.second.getStringRepresentationOfPrimitiveType()=="int"){
                                cout<<" "<<content.second.getValueInIdentifier()->intValue<<endl;
                            }else if(content.second.getStringRepresentationOfPrimitiveType()=="string"){
                                cout<<" "<<content.second.getValueInIdentifier()->stringValue<<endl;
                            }else if(content.second.getStringRepresentationOfPrimitiveType()=="real"){
                                cout<<" "<<content.second.getValueInIdentifier()->realValue<<endl;
                            }else if(content.second.getStringRepresentationOfPrimitiveType()=="bool"){
                                cout<<" "<<content.second.getValueInIdentifier()->boolValue<<endl;
                            }
                        }else{
                            cout<<endl;
                        }
                    }
                }
            } else if (input == "#load") { //if load is entered
                cout<<"Please enter the file name , make sure it is in the folder CompilersAssignment/TestPrograms"<<endl;
                cout<<"MLI> ";
                getline(cin,input); // get file name
                lexer->initialize_input_characters("TestPrograms/"+input); //initialize characters with file name

                /* This was used to test the lexer only , to view test , just remove the comments
                auto* token = lexer->getNextToken();
                while(token->getTokenType() != Token::TOK_EOF){
                    cout<<token->getTokenName()<<" ";
                    token = lexer->getNextToken();
                } */

                /* This was used to test the parser and xml generator only , to view test , just remove the comments*/
                //xml->visitTree(parser->parse());

                interpreterExecutor->visitTree(parser->parse()); // create parse tree and call interpreter on it
                lexer->clearCharactersContainer(); // clear characters to start from the beginning next time round
                lexer->restartCurrentInputIndex(); // restart pointer from beginning
                parser->resetAST(); // empty AST to start from the beginning next time round
            } else if (input == "#exit") {
                break; //if exit is entered break from the loop
            } else { //if another input is entered
                lexer->initializeCharactersWithString(input); //initialize the character stream by that input
                interpreterExecutor->visitTree(parser->parse()); // create parse tree and call interpreter executor on it (note validator is called implicitly)
                lexer->clearCharactersContainer(); //clear characters to start from the beginning next time round
                lexer->restartCurrentInputIndex(); // restart pointer from beginning
                parser->resetAST(); // empty AST to start from the beginning next time round
            }
        } catch (CompilingErrorException &e) { //if any compiling exception is met
            cout << e.getErrorMessage() << endl; // display error message and restart from initial state , otherwise same message will be displayed even for different input
            lexer->clearCharactersContainer();
            lexer->restartCurrentInputIndex();
            parser->resetAST();
            auto * previousScope = new vector<SymbolTable*>();
            for(unsigned int i=0;i<scopedTemp.size();i++){ //get previous state , this works since in the interpreter
                                                           // we are always in the global scope.
                if(interpreterExecutor->getValidator()->getScopedTable().at(i)->getMultimap().size() ==
                        scopedTemp.at(i).getMultimap().size()){
                    previousScope->push_back(interpreterExecutor->getValidator()->getScopedTable().at(i));
                }else{
                    tempValue=scopedTemp.at(i);
                    previousScope->push_back(&tempValue);
                }
            }
            interpreterExecutor->getValidator()->setScopedTable(*previousScope);
        }
        scopedTemp.clear();
        cout << "MLI> ";
        getline(cin, input); //get next input
    }
    cout << "Bye :)" << endl; // give nice message
    delete (interpreterExecutor, parser, lexer); //delete from heap
    return 0;
}