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
        return parseAssignStatement();
    }else{
        cout<<"Bad Statement"<<endl;
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
        cout<<"Forgot opening brackets in function declaration"<<endl;
        exit(-1);
    }
    lookAhead();
    auto * actualParams = new vector<ASTExprNode*>();
    if(nextToken->getTokenStringValue() != ")" && nextToken->getTokenType() != Lexer::Token::TOK_EOF){ //since if hello( .. tries to parse expr
        lookAhead();
        actualParams = &*parseActualParams();
    }
    if(nextToken->getTokenStringValue() != ")"){
        cout<<"Forgot closing brackets in function declaration"<<endl;
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
    lookAhead();
    if(nextToken->getTokenStringValue() == ")"){
        cout<<"forgot expression"<<endl;
        exit(-1);
    }
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
    return nullptr;
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
            cout<<"Statement Incomplete"<<endl;
            exit(-1);
        }
        lookAhead();
        return new ASTAssignStatementNode(identifier,parseExpression());
    }else{
        cout<<"Forgot equals in assignment"<<endl;
        exit(-1);
    }
}







