//
// Created by Dylan Galea on 07/04/2018.
//

/**
 * This class is used to encode an AST string literal expression node , where this is created whenever a lexer outputs
 * a TOK_STRING_LITERAL and the EBNF in the specification sheet is followed. This is a concrete child of the class
 * ASTLiteralExprNode , thus containing the setter,getter,expressionType related to the enum ExpressionType , and must
 * implement the inherited virtual accept method.This node stores the string literal that is passed by the lexer in
 * TOK_STRING_LITERAL.
 */

#ifndef COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
#include <string>
#include "../ASTExprNode.h"
#include "ASTLiteralExprNode.h"

using namespace std;

namespace AST{
    class ASTStringLiteralExprNode:public ASTLiteralExprNode {
    private:
        string sentence; //stores the sentence passed by the lexer in TOK_STRING_LITERAL
    public:
        /**
         * The constructor used to initialize a new ASTStringLiteralExprNode , storing the string value passed in @param
         * sentence in this->sentence.
         * @param sentence
         * Contains the string value that will be stored in this->sentence
         */
        explicit ASTStringLiteralExprNode(string sentence);
        /**
         * Default Destructor
         */
        ~ASTStringLiteralExprNode();
        /**
         * The setter method used to give a value to the private this->sentence variable
         * @param sentence
         * Stores the sentence string that will be assigned to this->sentence
         */
        void setValue(string sentence);
        /**
         * The getter method used to get the value stored in this->sentence.
         * @return
         * The string value in this->sentence.
         */
        string getValue();
        /**
         * The implementation of the inherited method
         * @param v
         * Stores a pointer to the visitor that is visiting this node
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
