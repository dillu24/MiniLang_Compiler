//
// Created by Dylan Galea on 04/04/2018.
//

#include "PredictiveParser.h"
#include "../ASTHierarchy/Expression/ASTBooleanLiteralExpressionNode.h"
#include "../ASTHierarchy/Expression/ASTStringLiteralExprNode.h"
#include "../ASTHierarchy/Expression/ASTBinaryExprNode.h"
#include "../Exceptions/CompilingErrorException.h"
using namespace Exception;

Parser::PredictiveParser::PredictiveParser(LexerImplementation *lex) {
    lexer = &*lex;
    currentToken = new Token();
    nextToken = new Token();
    tree = new vector<AST::ASTStatementNode*>();
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

vector<ASTStatementNode *>* Parser::PredictiveParser::parse() {
    nextToken = lexer->getNextToken();
    while(nextToken->getTokenType() != Lexer::Token::TOK_EOF){ //untill all tokens have been parsed
        lookAhead(); //get next token
        tree->push_back(parseStatement()); // parse the statement related to that token
    }
    return tree;
}


void Parser::PredictiveParser::lookAhead() {
    if(nextToken->getTokenType() == Token::TOK_EOF){ //if EOF the Parser has consumed all tokens , thus there must be an error in the program
        throw Exception::CompilingErrorException("Lexer has run out of tokens , there must be something wrong syntactically with the program");
    }
    currentToken = &*nextToken;
    nextToken = &*lexer->getNextToken();
}

ASTStatementNode *Parser::PredictiveParser::parseStatement() {
    if(currentToken->getTokenStringValue()=="set"){ //if the token is set , parse the set statement according to EBNF
        ASTAssignStatementNode* assign = parseAssignStatement();
        if(nextToken->getTokenStringValue() != ";"){ //If this happens then the statement did not end with a semi colon
            throw CompilingErrorException("Statement did not end with semi colon for var "+assign->getIdentifier()->getIdentifierName());
        }
        lookAhead(); //stop on semi colon , so that in the parse statement we can start from the next statement
        return assign;
    }else if(currentToken->getTokenStringValue() =="var"){ //if next statement is a var statement , parse var
        ASTVarDeclStatementNode* varDec = parseVarDecl();
        if(nextToken->getTokenStringValue() != ";"){ // this happens when statement does not end with semi colon
            throw CompilingErrorException("Statement did not end with semi colon for var "+varDec->getIdentifier()->getIdentifierName());
        }
        lookAhead(); //stop on semi colon , to start from the next statement
        return varDec;
    }else if(currentToken->getTokenStringValue() == "print"){ //if print statement start parse it according to EBNF
        ASTPrintStatementNode* print = parsePrintStatement();
        if(nextToken->getTokenStringValue() != ";"){ // if this happens source input program does not end with semi colon , therefore syntax error
            throw CompilingErrorException("Semi colon did not end printing statement");
        }
        lookAhead();
        return print;
    }else if (currentToken->getTokenStringValue() == "return"){ //if return statement parse return statement
        ASTReturnStatementNode* returnStatement = parseReturnStatement();
        if(nextToken->getTokenStringValue() != ";"){ // if the statement does not end with a semi colon , then we have a syntax error
            throw CompilingErrorException("Semi colon did not end return statement");
        }
        lookAhead(); //stop on semi colon so that parser can parse the next statement
        return returnStatement;
    }else if (currentToken->getTokenStringValue() == "{"){ //an opening curly bracket means a block must be parsed according to EBNF
        return parseBlockStatement();
    }else if(currentToken->getTokenStringValue() == "if"){ // and if token means an if staement must be parsed according to EBNF
        return parseIfStatement();
    }else if(currentToken->getTokenStringValue()== "while"){ // a while token means a while statement must be parsed according to EBNF
        return parseWhileStatement();
    }else if(currentToken->getTokenStringValue() == "def"){//a def token means a function definition must be pased according to EBNF
        return parseFunctionDefinition();
    }else{ //if none of the above is matched, then the program must have an invalid statement , thus throw exception for syntax errors.
        throw CompilingErrorException("invalid statement");
    }
}

ASTLiteralExprNode *Parser::PredictiveParser::parseLiteral() {
    /*A literal can be a number,boolean or string , thus if one of these are matched , the respective node is created.
    *However if none are matches the program expects a literal , thus there must be an error with the syntax of the
    *source input , thus the parser must stop parsing*/
    if(currentToken->getTokenType() == Lexer::Token::TOK_NUMBER){
        auto *numbNode = new ASTNumberExprNode(currentToken->getTokenValue());
        if(currentToken->getTokenName() == "REAL NUMBER"){ //store the type of the number accordingly
            numbNode->setNumberType(ASTNumberExprNode::REAL);
        }else if(currentToken->getTokenName() == "INTEGER NUMBER"){
            numbNode->setNumberType(ASTNumberExprNode::INT);
        }
        return numbNode;
    }else if(currentToken->getTokenStringValue() =="true"){
        return new ASTBooleanLiteralExpressionNode(true);
    }else if(currentToken->getTokenStringValue() =="false"){
        return new ASTBooleanLiteralExpressionNode(false);
    }else if(currentToken->getTokenType() == Lexer::Token::TOK_STRING_LITERAL) {
        return new ASTStringLiteralExprNode(currentToken->getTokenStringValue());
    }else{
        throw CompilingErrorException("Expecting Literal");
    }
}

ASTIdentifierExprNode *Parser::PredictiveParser::parseIdentifier() {
    /*
     * If the program expects and identifier and it is the current token that is being parsed , then create a new identifier
     * AST node , otherwise there must be a syntax error , thus terminate parser with an error message
     */
    if(currentToken->getTokenType() == Lexer::Token::TOK_IDENTIFIER){
        return new ASTIdentifierExprNode(currentToken->getTokenStringValue());
    }else{
        throw CompilingErrorException("Bad identifier");
    }
}

ASTExprNode *Parser::PredictiveParser::parseExpression() {
    /*parse according to EBNF,if some pattern is not matched then there must be a syntax error , therefore terminate parser
     *with error message , the structure how the EBNF is written handles the precedence of operators automatically.
     */
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
    /*parse according to EBNF,if some pattern is not matched then there must be a syntax error , therefore terminate parser
     *with error message , the structure how the EBNF is written handles the precedence of operators automatically.
     */
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
    /*
     *If one of the types of the minilang is needed to be parsed as current token when the program expects to , then
     * return the type according to the enum , to be stored in the AST node . If none of these types are matched, then
     * there must be an error in the syntax of the program , thus the parser must terminate with an error message.
     */
    if(currentToken->getTokenStringValue() == "real"){
        return AST::Type::REAL;
    }else if (currentToken->getTokenStringValue() =="int"){
        return AST::Type::INT;
    }else if(currentToken->getTokenStringValue()=="bool"){
        return AST::Type::BOOL;
    }else if(currentToken->getTokenStringValue()=="string"){
        return AST::Type::STRING;
    }else{
        throw CompilingErrorException("Bad type");
    }
}

Operators Parser::PredictiveParser::parseOperator() {
    /*
     *If one of the operators of the minilang is needed to be parsed as current token when the program expects to , then
     * return the operator according to the enum , to be stored in the AST node . If none of these operators are matched, then
     * there must be an error in the syntax of the program , thus the parser must terminate with an error message.
     */
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
        throw CompilingErrorException("Bad operator");
    }
}

ASTFnCallExprNode *Parser::PredictiveParser::parseFnCall() {
    ASTIdentifierExprNode* identifier = parseIdentifier(); //first parse identifier according to ebnf
    if(nextToken->getTokenStringValue() != "("){ // if the next token is not an opening of brackets , then this is a syntax error
        throw CompilingErrorException("Forgot opening brackets in function call");
    }
    lookAhead();
    auto * actualParams = new vector<ASTExprNode*>();
    //if the next token is not the eof , and not the closing brackets , then there must be parameters in between , therefore parse them
    if(nextToken->getTokenStringValue() != ")" && nextToken->getTokenType() != Lexer::Token::TOK_EOF){
        lookAhead();
        actualParams = &*parseActualParams();
    }
    //if after parsing the parameters there is no closing of square brackets , then this is a syntax error
    if(nextToken->getTokenStringValue() != ")"){
        throw CompilingErrorException("Forgot closing brackets in function call");
    }
    lookAhead();
    auto * fnCall = new ASTFnCallExprNode(identifier); //create node if everything went well
    for (auto &actualParam : *actualParams) {
        fnCall->addParameters(actualParam); //add to the list of parameters the parameters
    }
    return fnCall;
}

vector<ASTExprNode *>* Parser::PredictiveParser::parseActualParams() {
    auto * parameters = new vector<ASTExprNode*>();
    parameters->push_back(parseExpression()); //parse first parameter , since it must be present if the program came to this point
    while(nextToken->getTokenStringValue()!= ")"){ //untill closing of brackets parse parameters and check if commas separate them
        if(nextToken->getTokenStringValue() == ",") {
            lookAhead();
        }else{
            throw CompilingErrorException("Forgot comma in parameters");
        }
        if(nextToken->getTokenType() == Token::TOK_EOF){ //if no brackets are closed till EOF tell the user that he has a syntax error
            throw CompilingErrorException("Forgot to close brackets in function call");
        }
        lookAhead();
        parameters->push_back(parseExpression());
    }
    return parameters;
}

ASTSubExprNode *Parser::PredictiveParser::parseSubExpr() {
    /*
     * Parse sub expression according to ebnf , if these are not met then there is a syntax error in the input program,
     * this implementation of sub expression does not accept an empty sub expression , i.e having () only , since this
     * is then parsed as for example set x = ;
     */
    if(nextToken->getTokenStringValue() == ")" || nextToken->getTokenType() == Lexer::Token::TOK_EOF){
        throw CompilingErrorException("Forgot Expression");
    }
    lookAhead();
    ASTExprNode* expression = parseExpression();
    if(nextToken->getTokenStringValue() != ")"){
        throw CompilingErrorException("forgot closing brackets in sub expression");
    }
    lookAhead();
    return new ASTSubExprNode(expression);
}

ASTUnaryExprNode *Parser::PredictiveParser::parseUnary() {
    NegationOperator negOperator = parseNegOp(); //first parse negation operator
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ // if the expression is not present notify the user
        throw CompilingErrorException("forgot expression");
    }
    lookAhead();
    ASTExprNode* expression = parseExpression();
    return new ASTUnaryExprNode(negOperator,expression); //create node as required
}

NegationOperator Parser::PredictiveParser::parseNegOp() {
    /*
     * This function tries to match the operator that is used for negation , if one of -,not is matched the respective
     * value from the NegationType enum is returned , otherwise the program was expected to parse a negation operator
     * whilst it encountered something else , thus the parser stops with an error message.
     */
    if(currentToken->getTokenStringValue() == "-"){
        return AST::NegationOperator::MINUS;
    }else if(currentToken->getTokenStringValue() == "not"){
        return AST::NegationOperator::NOT;
    }else {
        throw CompilingErrorException("Bad negation operator");
    }
}

ASTVarDeclStatementNode *Parser::PredictiveParser::parseVarDecl() {
    lookAhead();
    ASTIdentifierExprNode* identifier = &*parseIdentifier(); //According to ebnf first parse identifier
    if(nextToken->getTokenStringValue() == ":"){ // if : is present
        lookAhead();
        if(!nextToken->getTokenType() == Lexer::Token::TOK_KEYWORD){ //keep on matching ebnf accordingly , and notify if not matched
            throw CompilingErrorException("Forgot type in declaring "+identifier->getIdentifierName());
        }
        lookAhead();
        Type type = parseType();
        if(nextToken->getTokenType() != Lexer::Token::TOK_EQUALS){
            throw CompilingErrorException("Forgot equals assignment when declaring "+identifier->getIdentifierName());
        }
        lookAhead();
        if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){
            throw CompilingErrorException("Forgot expression when declaring variable "+identifier->getIdentifierName());
        }
        lookAhead();
        ASTExprNode* expr = &*parseExpression();
        return new ASTVarDeclStatementNode(identifier,type,expr);
    }else{ //user forgot : therefore stop program and notify him
        throw CompilingErrorException("Forgot colon when declaring variable "+identifier->getIdentifierName());
    }
}

ASTExprNode *Parser::PredictiveParser::parseFactor() {
    //if one of the literals is matched parse the literal
    if(currentToken->getTokenType() == Lexer::Token::TOK_STRING_LITERAL || currentToken->getTokenType() == Lexer::Token::
            TOK_NUMBER || currentToken->getTokenStringValue() == "true"|| currentToken->getTokenStringValue() == "false"){
        return parseLiteral();
    //if an identifier is matched , parse an identifier expression if there is no opening brackets,and parse a function call
    // if there is an opening of brackets , since this signifies a function.
    }else if(currentToken->getTokenType() == Lexer::Token::TOK_IDENTIFIER){
        if(nextToken->getTokenStringValue() == "("){
            return parseFnCall();
        }else{
            return parseIdentifier();
        }
    //parse sub expression if ( is identified
    }else if(currentToken->getTokenStringValue() == "("){
        return parseSubExpr();
    // if - or not is ecountered , a unary expression must be parsed
    }else if(currentToken->getTokenType() == Lexer::Token::TOK_MINUS || currentToken->getTokenStringValue()=="not"){
        return parseUnary();
    }else{// if none of the above has been matched then there must be a syntax error.
        throw CompilingErrorException("Invalid factor");
    }
}

ASTExprNode *Parser::PredictiveParser::parseTerm() {
    /*
     * Parse term according to the ebnf specification
     */
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
    ASTIdentifierExprNode* identifier = parseIdentifier(); //parse identifier to be assigned
    if(nextToken->getTokenType() == Lexer::Token::TOK_EQUALS){ // if there is an equals continue parsing
        lookAhead();
        if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ // if user forgot expression notify by an error message
            throw CompilingErrorException("Forgot expression when assigning variable "+identifier->getIdentifierName());
        }
        lookAhead();
        return new ASTAssignStatementNode(identifier,parseExpression()); //create required node if everything is matched
    }else{ // otherwise signal an error
        throw CompilingErrorException("Forgot equals when assigning variable "+identifier->getIdentifierName());
    }
}

ASTPrintStatementNode *Parser::PredictiveParser::parsePrintStatement() {
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ //if user forgot expression print error message
        throw CompilingErrorException("Forgot expression when printing");
    }
    lookAhead();
    return new ASTPrintStatementNode(parseExpression()); // if everything is matched create print node
}

ASTReturnStatementNode *Parser::PredictiveParser::parseReturnStatement() {
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ //if user forgot return expression notfy him with error message
        throw CompilingErrorException("Forgot returning expression");
    }
    lookAhead();
    return new ASTReturnStatementNode(parseExpression());// if everything is matched create return node
}

ASTBlockStatementNode *Parser::PredictiveParser::parseBlockStatement() {
    auto * blockStatements = new vector<ASTStatementNode*>(); //stores the pointers to block statements
    while(nextToken->getTokenStringValue() != "}"){ // untill the scope is not closed
        if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ // if an EOF is met then the user forgot to close scope
            throw CompilingErrorException("Forgot closing scope");
        }
        lookAhead();
        blockStatements->push_back(parseStatement()); // parse statement in scope
    }
    lookAhead();
    return new ASTBlockStatementNode(blockStatements); //create required scope if everything is matched
}

ASTIfStatementNode *Parser::PredictiveParser::parseIfStatement() {
    /*
     * This function is implemented by always trying to lookahead at the next token to see if terminals are being
     * inputted by the user , so that if everything matches , an appropiate if statement node is created
     */
    if(nextToken->getTokenStringValue() != "("){ //syntax error if user forgot to open brackets
        throw CompilingErrorException("Forgot opening round brackets in if statement");
    }
    lookAhead();
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ //if user forgot to put expression notfy with error message
        throw CompilingErrorException("Forgot Expression");
    }
    lookAhead();
    ASTExprNode* expr = parseExpression(); //parse the expression
    if(nextToken->getTokenStringValue() !=")"){ //if user forgot to close brackets notify with error message
        throw CompilingErrorException("Forgot closing brackets in if statement");
    }
    lookAhead();
    if(nextToken->getTokenStringValue() != "{"){ //if user forgot scope notify with error message
        throw CompilingErrorException("Forgot opening scope in if statement");
    }
    lookAhead();
    ASTBlockStatementNode* block = parseBlockStatement();
    if(nextToken->getTokenStringValue() == "else"){ // if user has else statement
        lookAhead();
        if(nextToken->getTokenStringValue() != "{"){ // report error if he forgot scope
            throw CompilingErrorException("Forgot opening scope in else block");
        }
        lookAhead();
        ASTBlockStatementNode* eBlock = parseBlockStatement();
        return new ASTIfStatementNode(expr,block,eBlock); //create if block accordingly
    }else{ //if user does not have else statement , create if block accordingly
        return new ASTIfStatementNode(expr,block, nullptr);
    }
}

ASTWhileStatementNode *Parser::PredictiveParser::parseWhileStatement() {
    if(nextToken->getTokenStringValue() != "("){ //if user forgot to open brackets notify with error message
        throw CompilingErrorException("Forgot opening brackets in while statement");
    }
    lookAhead();
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ //if user forgot to put expression notify with error message
        throw CompilingErrorException("Forgot expression in while statement");
    }
    lookAhead();
    ASTExprNode* expr = parseExpression();
    if(nextToken->getTokenStringValue() != ")"){ //if user forgot to close expression notify with error message
        throw CompilingErrorException("Forgot closing brackets in while statement");
    }
    lookAhead();
    if(nextToken->getTokenStringValue() != "{"){ // if user forgot to open scope notify with error message
        throw CompilingErrorException("Forgot opening scope in while statement");
    }
    lookAhead();
    ASTBlockStatementNode* block = parseBlockStatement(); //parse block
    return new ASTWhileStatementNode(expr,block); //return new while node accordingly
}

FormalParam *Parser::PredictiveParser::parseFormalParam() {
    ASTIdentifierExprNode * identifier = parseIdentifier(); //first parse identifier
    if(nextToken->getTokenStringValue() != ":"){ // if semi colon is not found report error
        throw CompilingErrorException("Forgot : in parameters");
    }
    lookAhead();
    if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ //if eof is matched then the parameters are not entered
        throw CompilingErrorException("Forgot type in parameters");
    }
    lookAhead();
    Type type = parseType();
    return new FormalParam(identifier,type); //return required pointer
}

FormalParams *Parser::PredictiveParser::parseFormalParams() {
    if(currentToken->getTokenType() == Lexer::Token::TOK_IDENTIFIER){
        FormalParam* fp = parseFormalParam(); //acording to ebnf first parse formalParam
        auto * formalParams = new FormalParams(fp);
        while(nextToken->getTokenStringValue() != ")"){ //untill bracket is closed keep on reading parameters defn
            if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ // if this is met user forgot to close brackets
                throw CompilingErrorException("Didn't close brackets in parameters");
            }
            if(nextToken->getTokenStringValue() != ","){ //check each parameter is split by a comma
                throw CompilingErrorException("Forgot comma in parameters");
            }
            lookAhead(); // lookahead 2 times to get next valid parameters
            lookAhead();
            formalParams->parameters.push_back(parseFormalParam()); //add parameters
        }
        return formalParams;
    }else{ //return if the identifier for formal param is not found
        throw CompilingErrorException("Forgot identifier for formal param");
    }
}

ASTFuncDeclStatementNode *Parser::PredictiveParser::parseFunctionDefinition() {
    if(nextToken->getTokenType() == Lexer::Token::TOK_IDENTIFIER){ //if an identifier of the function is found
        lookAhead();
        ASTIdentifierExprNode* identifier = parseIdentifier(); // parse identifier
        FormalParams* fp = nullptr;
        if(nextToken->getTokenStringValue() == "("){ //check if function definition continues with opening of brackets
            lookAhead();
            if(nextToken->getTokenStringValue() != ")"){ // if there is no closing of brackets immediately , there
                                                         //must be parameters to be parsed
                lookAhead();
                fp = parseFormalParams();
            }
            if(nextToken->getTokenStringValue() != ")"){ // after parameters have been parsed check if brackets have been closed
                throw CompilingErrorException("Forgot closing brackets in defining function "+identifier->getIdentifierName());
            }
            lookAhead();
            if(nextToken->getTokenStringValue() != ":"){ //check if semi colon is enetered otherwise notify with error message
                throw CompilingErrorException("Forgot : in defining function "+identifier->getIdentifierName());
            }
            lookAhead();
            if(nextToken->getTokenType() == Lexer::Token::TOK_EOF){ // if user forgot to conitnue writing report error
                throw CompilingErrorException("Forgot returning type of function "+identifier->getIdentifierName());
            }
            lookAhead();
            Type type = parseType();
            if(nextToken->getTokenStringValue() != "{"){ // check if scope is opened , otherwise return error
                throw CompilingErrorException("Forgot opening scope of function "+identifier->getIdentifierName());
            }
            lookAhead();
            ASTBlockStatementNode* block = parseBlockStatement();
            return new ASTFuncDeclStatementNode(identifier,fp,type,block); // create fn defn node if everything is matched
        }else{ //if no bracket shave been opened notify with error message
            throw CompilingErrorException("Forgot opening brackets when defining function "+identifier->getIdentifierName());
        }
    }else{ // if the function was not given a name notify the user
        throw CompilingErrorException("Function was not given a name");
    }
}

void Parser::PredictiveParser::resetAST() {
    tree->clear();
}







