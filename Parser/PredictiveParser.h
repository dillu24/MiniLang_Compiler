//
// Created by Dylan Galea on 04/04/2018.
//

/**
 * This class is used to implement the Recursive Descendt Predictive parser , each EBNF non terminal thus must be parsed
 * and a parse method is created for each ,in order to create the respective nodes.
 */

#ifndef COMPILERSASSIGNMENT_PREDICTIVEPARSER_H
#define COMPILERSASSIGNMENT_PREDICTIVEPARSER_H

#include "../Lexer/LexerImplementation.h"
#include "../ASTHierarchy/ASTNode.h"
#include "../ASTHierarchy/ASTStatementNode.h"
#include "../ASTHierarchy/Expression/ASTNumberExprNode.h"
#include "../ASTHierarchy/Statement/ASTPrintStatementNode.h"
#include "../ASTHierarchy/Statement/ASTVarDeclStatementNode.h"
#include "../ASTHierarchy/Operators.h"
#include "../ASTHierarchy/Expression/ASTFnCallExprNode.h"
#include "../ASTHierarchy/Expression/ASTSubExprNode.h"
#include "../ASTHierarchy/Expression/ASTUnaryExprNode.h"
#include "../ASTHierarchy/Statement/ASTAssignStatementNode.h"
#include "../ASTHierarchy/Statement/ASTReturnStatementNode.h"
#include "../ASTHierarchy/Statement/ASTBlockStatementNode.h"
#include "../ASTHierarchy/Statement/ASTIfStatementNode.h"
#include "../ASTHierarchy/Statement/ASTWhileStatementNode.h"
#include "../ASTHierarchy/Statement/FormalParam.h"
#include "../ASTHierarchy/Statement/FormalParams.h"
#include "../ASTHierarchy/Statement/ASTFuncDeclStatementNode.h"

using namespace Lexer;
using namespace AST;

namespace Parser{
    class PredictiveParser {
    private:
        LexerImplementation *lexer; // Stores the address of the Lexer
        Token *currentToken; // Stores the address of the current token being parsed
        Token *nextToken; // stores the address of the next token to be parsed.
        vector<ASTStatementNode*> *tree; //stores the AST that was outputted from the list of tokens .. the root node is the vector pointer itself
                                         // where the content is the different branches
        /**
         * This method is used to switch the value of this->currentToken to this->nextToken , and the value of this->nextToken
         * is assigned to the value returned by the Lexer::getNextToken() method in order to parse more tokens.
         */
        void lookAhead();
        /**
         * This method is used to parse a statement according to the EBND given in the specification sheet
         * @return
         * An ASTStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only. Note each statement has a branch in the AST.
         */
        ASTStatementNode* parseStatement();
        /**
         * This method is used to parse a literal according to the EBNF given in the specification sheet
         * @return
         * An ASTLiteralExprNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that expression only.
         */
        ASTLiteralExprNode * parseLiteral();
        /**
         * This method is used to parse a variable declaration according to the EBNF given in the specification sheet
         * @return
         * An ASTVarDeclStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTVarDeclStatementNode* parseVarDecl();
        /**
         * This method is used to parse an identifier according to the EBNF given in the specification sheet
         * @return
         * An ASTIdentifierExprNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that expression only.
         */
        ASTIdentifierExprNode* parseIdentifier();
        /**
         * This method is used to parse an expression according to the EBNF given in the specification sheet
         * @return
         * An ASTExprNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that expression only.
         */
        ASTExprNode* parseExpression();
        /**
         * This method is used to parse a simple expression according to the EBNF given in the specification sheet
         * @return
         * An ASTExprNode* pointer which points to a branch of the syntax tree representing the syntax tree for
         * that expression only.
         */
        ASTExprNode* parseSimpleExpr();
        /**
         * This method is used to parse an operator according to the EBNF given in the specification sheet
         * @return
         * An Operator type which stores an operator of the MiniLang language.
         */
        Operators parseOperator();
        /**
         * This method is used to parse a Type according to the EBNF given in the specification sheet
         * @return
         * An Type type which stores a valid type of MINILANG
         */
        Type parseType();
        /**
        * This method is used to parse a function call according to the EBNF given in the specification sheet
        * @return
        * An ASTVFnCallExprNode pointer which points to a branch of the syntax tree representing the syntax tree for
        * that expression only.
        */
        ASTFnCallExprNode* parseFnCall();
        /**
         * This method is used to parse a parameters for function calls according to the EBNF given in the specification sheet
         * @return
         * A pointer to a vector of parameters storing the 0 or more parameters that make up the function call.
         */
        vector<ASTExprNode*>* parseActualParams();
        /**
         * This method is used to parse a sub expression according to the EBNF given in the specification sheet
         * @return
         * An ASTSubExprNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that expression only.
         */
        ASTSubExprNode* parseSubExpr();
        /**
         * This method is used to parse a unary expression according to the EBNF given in the specification sheet
         * @return
         * An ASTUnaryExprNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that expression only.
         */
        ASTUnaryExprNode* parseUnary();
        /**
         * This method is used to parse a negation operator according to the EBNF given in the specification sheet
         * @return
         * A negation operator value which is that negation operator that makes up the parsed expression
         */
        NegationOperator parseNegOp();
        /**
         * This method is used to parse a factor according to the EBNF given in the specification sheet
         * @return
         * An ASTExprNode* pointer which points to a branch of the syntax tree representing the syntax tree for
         * that expression only.
         */
        ASTExprNode* parseFactor();
        /**
         * This method is used to parse a term according to the EBNF given in the specification sheet
         * @return
         * An ASTExprNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that expression only.
         */
        ASTExprNode* parseTerm();
        /**
         * This method is used to parse an assignment statement according to the EBNF given in the specification sheet
         * @return
         * An ASTAssignStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTAssignStatementNode* parseAssignStatement();
        /**
         * This method is used to parse a print statement according to the EBNF given in the specification sheet
         * @return
         * An ASTPrintStatementNode which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTPrintStatementNode* parsePrintStatement();
        /**
         * This method is used to parse a return statement according to the EBNF given in the specification sheet
         * @return
         * An ASTReturnStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTReturnStatementNode* parseReturnStatement();
        /**
         * This method is used to parse a block statement according to the EBNF given in the specification sheet
         * @return
         * An ASTBlockStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTBlockStatementNode* parseBlockStatement();
        /**
         * This method is used to parse an if statement according to the EBNF given in the specification sheet
         * @return
         * An ASTIfStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTIfStatementNode* parseIfStatement();
        /**
         * This method is used to parse a while statement according to the EBNF given in the specification sheet
         * @return
         * An ASTWhileStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTWhileStatementNode* parseWhileStatement();
        /**
         * This method is used to parse formal parameters for function definition according to the EBNF given in the
         * specification sheet
         * @return
         * A FormalParam pointer which points to the 0 or more function definition parameters
         */
        FormalParam* parseFormalParam();
        /**
        * This method is used to parse formal parameters for function definition according to the EBNF given in the
        * specification sheet
        * @return
        * A FormalParams pointer which points to the 0 or more function definition parameters
        */
        FormalParams* parseFormalParams();
        /**
         * This method is used to parse a function definition according to the EBNF given in the specification sheet
         * @return
         * An ASTFuncDeclStatementNode pointer which points to a branch of the syntax tree representing the syntax tree for
         * that statement only.
         */
        ASTFuncDeclStatementNode* parseFunctionDefinition();
    public :
        /**
         * This constructor is used to create a new parser initialized with the lexer that is going to be used
         * @param lex
         * Stores the address of the lexer that is going to be used to produce tokens
         */
        explicit PredictiveParser(LexerImplementation *lex);
        /**
         * The destructor used to delete all parser related data from the heap
         */
        ~PredictiveParser();
        /**
         * This method is used to start the parsing mechanism by converting the stream of tokens into a parse tree
         * so that the program structure can be validated if correct or not.
         * @return
         * A vector of AST statement nodes , i.e the AST were the pointer to the vector is itself the root of the AST
         * and the elements in the vector are the branches of the AST.
         */
        vector<ASTStatementNode*>* parse();

        /**
         * This method is used to reset the AST to empty , so that the REPL can build a new AST for each statement input.
         * Otherwise the InterpreterExecutor keeps on executing previously types expressions.
         */

        void resetAST();
    };
}


#endif //COMPILERSASSIGNMENT_PREDICTIVEPARSER_H
