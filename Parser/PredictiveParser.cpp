//
// Created by Dylan Galea on 04/04/2018.
//

#include "PredictiveParser.h"
#include "../ASTHierarchy/Expression/ASTBooleanLiteralExpressionNode.h"
#include "../ASTHierarchy/Expression/ASTStringLiteralExprNode.h"
#include "../ASTHierarchy/Expression/ASTBinaryExprNode.h"

Parser::PredictiveParser::PredictiveParser(LexerImplementation *lex) {
    lexer = &*lex;
    currentToken = new Token();
    nextToken = new Token();
    tree = new vector<AST::ASTNode*>();
}

Parser::PredictiveParser::~PredictiveParser() {
    delete nextToken;
    delete currentToken;
    delete lexer;
    for (auto &i : *tree) {
        delete i;
    }
    delete tree;
}

vector<ASTNode *>* Parser::PredictiveParser::parse() {
    nextToken = lexer->getNextToken();
    while(nextToken->getTokenType() != Lexer::Token::TOK_EOF){
        lookAhead();
        //ASTStatementNode* answer = parseStatement(); //for testing purposes only ,put answer instaead of parse statement for test check
        tree->push_back(parseStatement());
    }
    cout<<tree->size()<<endl;
    return tree;
}


void Parser::PredictiveParser::lookAhead() {
    currentToken = &*nextToken;
    nextToken = &*lexer->getNextToken();
}

ASTStatementNode *Parser::PredictiveParser::parseStatement() {
    if(currentToken->getTokenStringValue()=="set"){
        ASTAssignStatementNode* assign = parseAssignStatement();
        if(nextToken->getTokenStringValue() != ";"){
            cout<<"Statement did not end with semi colon for var "<<assign->getIdentifier()->getIdentifierName()<<endl;
            exit(-1);
        }
        lookAhead();
        return assign;
    }else if(currentToken->getTokenStringValue() =="var"){
        ASTVarDeclStatementNode* varDec = parseVarDecl();
        if(nextToken->getTokenStringValue() != ";"){
            cout<<"Statement did not end with semi colon for var "<<varDec->getIdentifier()->getIdentifierName()<<endl;
            exit(-1);
        }
        lookAhead();
        return varDec;
    }else if(currentToken->getTokenStringValue() == "print"){
        ASTPrintStatementNode* print = parsePrintStatement();
        if(nextToken->getTokenStringValue() != ";"){
            cout<<"Semi colon did not end printing statement "<<endl;
            exit(-1);
        }
        lookAhead();
        return print;
    }else if (currentToken->getTokenStringValue() == "return"){
        ASTReturnStatementNode* returnStatement = parseReturnStatement();
        if(nextToken->getTokenStringValue() != ";"){
            cout<<"Semi colon did not end return statement"<<endl;
            exit(-1);
        }
        lookAhead();
        return returnStatement;
    }else if (currentToken->getTokenStringValue() == "{"){
        return parseBlockStatement();
    }else if(currentToken->getTokenStringValue() == "if"){
        return parseIfStatement();
    }else if(currentToken->getTokenStringValue()== "while"){
        return parseWhileStatement();
    }else if(currentToken->getTokenStringValue() == "def"){
        return parseFunctionDefinition();
    }else{
        cout<<"Invalid Statement"<<endl;
        exit(-1);
    }
}

ASTLiteralExprNode *Parser::PredictiveParser::parseLiteral() {
    if(currentToken->getTokenType() == Lexer::Token::TOK_NUMBER){
        return new ASTNumberExprNode(currentToken->getTokenValue());
    }else if(currentToken->getTokenStringValue() =="true"){
        return new ASTBooleanLiteralExpressionNode(true);
    }else if(currentToken->getTokenStringValue() =="false"){
        return new ASTBooleanLiteralExpressionNode(false);
    }else if(currentToken->getTokenType() == Lexer::Token::TOK_STRING_LITERAL) {
        return new ASTStringLiteralExprNode(currentToken->getTokenStringValue());
    }else{
        cout<<"Expecting Literal"<<endl;
        exit(-1);
    }
}

ASTIdentifierExprNode *Parser::PredictiveParser::parseIdentifier() {
    if(currentToken->getTokenType() == Lexer::Token::TOK_IDENTIFIER){
        return new ASTIdentifierExprNode(currentToken->getTokenStringValue());
    }else{
        cout<<"Bad identifier"<<endl;
        exit(-1);
    }
}

ASTExprNode *Parser::PredictiveParser::parseExpression() {
    ASTExprNode* simpleExpr = parseSimpleExpr();
    if(nextToken->getTokenType() == Lexer::Token::TOK_RELATIONAL_OPERATOR){
        lookAhead();
        Operators op = parseOperator();
        lookAhead();
        ASTExprNode* rhs = parseExpression();
        return new ASTBinaryExprNode(simpleExpr,rhs,op);
    }else{
        return simpleExpr;
    }
}

ASTExprNode *Parser::PredictiveParser::parseSimpleExpr() {
    ASTExprNode* term = parseTerm();
    if(nextToken->getTokenStringValue() == "+" || nextToken->getTokenStringValue() == "-" || nextToken->
            getTokenStringValue() == "or"){
        lookAhead();
        Operators op = parseOperator();
        lookAhead();
        ASTExprNode* rhs = parseSimpleExpr();
        return new ASTBinaryExprNode(term,rhs,op);
    }else{
        return term;
    }
}

Type Parser::PredictiveParser::parseType() {
    if(currentToken->getTokenStringValue() == "real"){
        return AST::Type::REAL;
    }else if (currentToken->getTokenStringValue() =="int"){
        return AST::Type::INT;
    }else if(currentToken->getTokenStringValue()=="bool"){
        return AST::Type::BOOL;
    }else if(currentToken->getTokenStringValue()=="string"){
        return AST::Type::STRING;
    }else{
        cout<<"Bad type"<<endl;
        exit(-1);
    }
}

Operators Parser::PredictiveParser::parseOperator() {
    if(currentToken->getTokenStringValue() == "-"){
        return AST::Operators::MINUS;
    }else if(currentToken->getTokenStringValue() == "+"){
        return AST::Operators::PLUS;
    }else if(currentToken->getTokenStringValue()== "/"){
        return AST::Operators::DIVISION;
    }else if(currentToken->getTokenStringValue()== "*"){
        return AST::Operators::TIMES;
    }else if(currentToken->getTokenStringValue()=="and"){
        return AST::Operators::AND;
    }else if(currentToken->getTokenStringValue()=="or"){
        return AST::Operators::OR;
    }else if(currentToken->getTokenStringValue()=="=="){
        return AST::Operators::EQUALTO;
    }else if(currentToken->getTokenStringValue()=="<="){
        return AST::Operators::LESSTHANEQUAL;
    }else if(currentToken->getTokenStringValue()==">="){
        return AST::Operators::GREATERTHANEQUAL;
    }else if(currentToken->getTokenStringValue()==">"){
        return AST::Operators::GREATERTHAN;
    }else if(currentToken->getTokenStringValue()=="<"){
        return AST::Operators::LESSTHAN;
    }else if(currentToken->getTokenStringValue()=="!="){
        return AST::Operators::NOTEQUAL;
    }else{
        cout<<"Bad operator"<<endl;
        exit(-1);
    }
}

ASTFnCallExprNode *Parser::PredictiveParser::parseFnCall() {
    ASTIdentifierExprNode* identifier = parseIdentifier();
    if(nextToken->getTokenStringValue() != "("){
        cout<<"Forgot opening brackets in function call"<<endl;
        exit(-1);
    }
    lookAhead();
    auto * actualParams = new vector<ASTExprNode*>();
    if(nextToken->getTokenStringValue() != ")" && nextToken->getTokenType() != Lexer::Token::TOK_EOF){ //since if hello( .. tries to parse expr
        lookAhead();
        actualParams = &*parseActualParams();
    }
    if(nextToken->getTokenStringValue() != ")"){
        cout<<"Forgot closing brackets in function call"<<endl;
        exit(-1);
    }
    lookAhead();
    auto * fnCall = new ASTFnCallExprNode(identifier);
    for (auto &actualParam : *actualParams) {
        fnCall->addParameters(actualParam);
    }
    return fnCall;
}

vector<ASTExprNode *>* Parser::PredictiveParser::parseActualParams() {
    auto * parameters = new vector<ASTExprNode*>();
    parameters->push_back(parseExpression());
    while(nextToken->getTokenStringValue()!= ")"){
        if(nextToken->getTokenStringValue() == ","){
            lookAhead();
        }else{
            cout<<"Forgot comma in parameters"<<endl;
            exit(-1);
        }
        lookAhead();
        parameters->push_back(parseExpression());
    }
    return parameters;
}

ASTSubExprNode *Parser::PredictiveParser::parseSubExpr() {
    if(nextToken->getTokenStringValue() == ")" || nextToken->getTokenType() == Lexer::Token::TOK_EOF){
        cout<<"forgot expression"<<endl;
        exit(-1);
    }
    lookAhead();
    ASTExprNode* expression = parseExpression();
    if(nextToken->getTokenStringValue() != ")"){
        cout<<"forgot closing brackets in sub expression"<<endl;
        exit(-1);
    }
    lookAhead();
    return new ASTSubExprNode(expression);
}

ASTUnaryExprNode *Parser::PredictiveParser::parseUnary() {
    NegationOperator negOperator = parseNegOp();
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
        cout<<"Forgot expression"<<endl;
        exit(-1);
    }
    lookAhead();
    ASTExprNode* expression = parseExpression();
    return new ASTUnaryExprNode(negOperator,expression);
}

NegationOperator Parser::PredictiveParser::parseNegOp() {
    if(currentToken->getTokenStringValue() == "-"){
        return AST::NegationOperator::MINUS;
    }else if(currentToken->getTokenStringValue() == "not"){
        return AST::NegationOperator::NOT;
    }else {
        cout<<"Bad negation operator"<<endl;
        exit(-1);
    }
}

ASTVarDeclStatementNode *Parser::PredictiveParser::parseVarDecl() {
    lookAhead();
    ASTIdentifierExprNode* identifier = &*parseIdentifier();
    if(nextToken->getTokenStringValue() == ":"){
        lookAhead();
        if(!nextToken->getTokenType() == Lexer::Token::TOK_KEYWORD){
            cout<<"Forgot type in declaring "<<identifier->getIdentifierName()<<endl;
            exit(-1);
        }
        lookAhead();
        Type type = parseType();
        if(nextToken->getTokenType() != Lexer::Token::TOK_EQUALS){
            cout<<"Forgot equals assignment when declaring "<<identifier->getIdentifierName()<<endl;
            exit(-1);
        }
        lookAhead();
        if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
            cout<<"Forgot expression when declaring variable "<<identifier->getIdentifierName()<<endl;
            exit(-1);
        }
        lookAhead();
        ASTExprNode* expr = &*parseExpression();
        return new ASTVarDeclStatementNode(identifier,type,expr);
    }else{
        cout <<"Forgot colon when declaring variable "<<identifier->getIdentifierName()<<endl;
        exit(-1);
    }
}

ASTExprNode *Parser::PredictiveParser::parseFactor() {
    if(currentToken->getTokenType() == Lexer::Token::TOK_STRING_LITERAL || currentToken->getTokenType() == Lexer::Token::
            TOK_NUMBER || currentToken->getTokenStringValue() == "true"|| currentToken->getTokenStringValue() == "false"){
        return parseLiteral();
    }else if(currentToken->getTokenType() == Lexer::Token::TOK_IDENTIFIER){
        if(nextToken->getTokenStringValue() == "("){
            return parseFnCall();
        }else{
            return parseIdentifier();
        }
    }else if(currentToken->getTokenStringValue() == "("){
        return parseSubExpr();
    }else if(currentToken->getTokenType() == Lexer::Token::TOK_MINUS || currentToken->getTokenStringValue()=="not"){
        return parseUnary();
    }else{
        cout<<"Invalid factor"<<endl;
        exit(-1);
    }
}

ASTExprNode *Parser::PredictiveParser::parseTerm() {
    ASTExprNode* factor = parseFactor();
    if(nextToken->getTokenStringValue() == "*" || nextToken->getTokenStringValue() =="/" ||
            nextToken->getTokenStringValue() == "and"){
        lookAhead();
        Operators op = parseOperator();
        lookAhead();
        ASTExprNode* rhs = parseTerm();
        return new ASTBinaryExprNode(factor,rhs,op);
    }else{
        return factor;
    }
}

ASTAssignStatementNode *Parser::PredictiveParser::parseAssignStatement() {
    lookAhead();
    ASTIdentifierExprNode* identifier = parseIdentifier();
    if(nextToken->getTokenType() == Lexer::Token::TOK_EQUALS){
        lookAhead();
        if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
            cout<<"Forgot expression when assigning variable "<<identifier->getIdentifierName()<<endl;
            exit(-1);
        }
        lookAhead();
        return new ASTAssignStatementNode(identifier,parseExpression());
    }else{
        cout<<"Forgot equals when assigning variable "<<identifier->getIdentifierName()<<endl;
        exit(-1);
    }
}

ASTPrintStatementNode *Parser::PredictiveParser::parsePrintStatement() {
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
        cout<<"Forgot expression when printing"<<endl;
        exit(-1);
    }
    lookAhead();
    return new ASTPrintStatementNode(parseExpression());
}

ASTReturnStatementNode *Parser::PredictiveParser::parseReturnStatement() {
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
        cout<<"Forgot returning expression"<<endl;
    }
    lookAhead();
    return new ASTReturnStatementNode(parseExpression());
}

ASTBlockStatementNode *Parser::PredictiveParser::parseBlockStatement() {
    auto * blockStatements = new vector<ASTStatementNode*>();
    while(nextToken->getTokenStringValue() != "}"){
        if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
            cout<<"Forgot closing scope"<<endl;
            exit(-1);
        }
        lookAhead();
        blockStatements->push_back(parseStatement());
    }
    lookAhead();
    return new ASTBlockStatementNode(blockStatements);
}

ASTIfStatementNode *Parser::PredictiveParser::parseIfStatement() {
    if(nextToken->getTokenStringValue() != "("){
        cout<<"Forgot opening brackets in if statement"<<endl;
        exit(-1);
    }
    lookAhead();
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
        cout<<"Forgot expression"<<endl;
        exit(-1);
    }
    lookAhead();
    ASTExprNode* expr = parseExpression();
    if(nextToken->getTokenStringValue() !=")"){
        cout<<"Forgot closing brackets in if statement"<<endl;
        exit(-1);
    }
    lookAhead();
    if(nextToken->getTokenStringValue() != "{"){
        cout<<"Forgot opening scope in if statement"<<endl;
        exit(-1);
    }
    lookAhead();
    ASTBlockStatementNode* block = parseBlockStatement();
    if(nextToken->getTokenStringValue() == "else"){
        lookAhead();
        if(nextToken->getTokenStringValue() != "{"){
            cout<<"Forgot opening scope in else block"<<endl;
            exit(-1);
        }
        lookAhead();
        ASTBlockStatementNode* eBlock = parseBlockStatement();
        return new ASTIfStatementNode(expr,block,eBlock);
    }else{
        return new ASTIfStatementNode(expr,block, nullptr);
    }
}

ASTWhileStatementNode *Parser::PredictiveParser::parseWhileStatement() {
    if(nextToken->getTokenStringValue() != "("){
        cout<<"Forgot opening brackets in while statement"<<endl;
        exit(-1);
    }
    lookAhead();
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
        cout<<"Forgot expression in while statement"<<endl;
        exit(-1);
    }
    lookAhead();
    ASTExprNode* expr = parseExpression();
    if(nextToken->getTokenStringValue() != ")"){
        cout<<"forgot closing brackets in while statement"<<endl;
        exit(-1);
    }
    lookAhead();
    if(nextToken->getTokenStringValue() != "{"){
        cout<<"forgot opening scope in while statement"<<endl;
        exit(-1);
    }
    lookAhead();
    ASTBlockStatementNode* block = parseBlockStatement();
    return new ASTWhileStatementNode(expr,block);
}

FormalParam *Parser::PredictiveParser::parseFormalParam() {
    ASTIdentifierExprNode * identifier = parseIdentifier();
    if(nextToken->getTokenStringValue() != ":"){
        cout<<"Forgot : in parameters"<<endl;
        exit(-1);
    }
    lookAhead();
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
        cout<<"Forgot Type in parameters"<<endl;
        exit(-1);
    }
    lookAhead();
    Type type = parseType();
    return new FormalParam(identifier,type);
}

FormalParams *Parser::PredictiveParser::parseFormalParams() {
    if(currentToken->getTokenType() == Lexer::Token::TOK_IDENTIFIER){
        FormalParam* fp = parseFormalParam();
        auto * formalParams = new FormalParams(fp);
        while(nextToken->getTokenStringValue() != ")"){
            if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
                cout<<"didn't close bracket in parameters"<<endl;
                exit(-1);
            }
            if(nextToken->getTokenStringValue() != ","){
                cout<<"Forgot comma in parameters"<<endl;
                exit(-1);
            }
            lookAhead();
            lookAhead();
            formalParams->parameters.push_back(parseFormalParam());
        }
        return formalParams;
    }else{
        cout<<"Forgot identifier for formal param"<<endl;
        exit(-1);
    }
}

ASTFuncDeclStatementNode *Parser::PredictiveParser::parseFunctionDefinition() {
    if(nextToken->getTokenType() == Lexer::Token::TOK_IDENTIFIER){
        lookAhead();
        ASTIdentifierExprNode* identifier = parseIdentifier();
        FormalParams* fp = nullptr;
        if(nextToken->getTokenStringValue() == "("){
            lookAhead();
            if(nextToken->getTokenStringValue() != ")"){
                lookAhead();
                fp = parseFormalParams();
            }
            if(nextToken->getTokenStringValue() != ")"){
                cout<<"Forgot closing brackets in defining function "<<identifier->getIdentifierName()<<endl;
                exit(-1);
            }
            lookAhead();
            if(nextToken->getTokenStringValue() != ":"){
                cout<<"Forgot : in defining function "<<identifier->getIdentifierName()<<endl;
                exit(-1);
            }
            lookAhead();
            if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
                cout<<"Forgot returning type of function "<<identifier->getIdentifierName()<<endl;
                exit(-1);
            }
            lookAhead();
            Type type = parseType();
            if(nextToken->getTokenStringValue() != "{"){
                cout<<"forgot block of function definition"<<endl;
                exit(-1);
            }
            lookAhead();
            ASTBlockStatementNode* block = parseBlockStatement();
            return new ASTFuncDeclStatementNode(identifier,fp,type,block);
        }else{
            cout<<"Forgot opening brackets when defining function "<<identifier->getIdentifierName()<<endl;
            exit(-1);
        }
    }else{
        cout<<"Function was not given a name"<<endl;
        exit(-1);
    }
}







