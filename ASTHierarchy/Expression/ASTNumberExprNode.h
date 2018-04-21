//
// Created by Dylan Galea on 06/04/2018.
//

/**
 * This class is used to encode an AST number node ,which is created whenever the parser meets a TOK_NUMBER from the lexer.
 * This is a concrete class , child of ASTLiteralExprNode and thus must implement the accept method inherited from
 * it's parents. This class stores the number that is passed in the TOK_NUMBER.
 */

#ifndef COMPILERSASSIGNMENT_ASTNUMBEREXPRNODE_H
#define COMPILERSASSIGNMENT_ASTNUMBEREXPRNODE_H

#include "../ASTExprNode.h"
#include "ASTLiteralExprNode.h"

namespace AST{
    class ASTNumberExprNode:public ASTLiteralExprNode {
    public:
        enum numberType{ //indicates whether the stored value is a real or int , used in visitor classes
            REAL,
            INT
        };
        /**
         * This constructor is used to initialize a new ASTNumberExprNode storing the value in @param val
         * @param val
         * Stores the value that will be stored in this->value
         */
        explicit ASTNumberExprNode(double val);
        /**
         * Default destructor , since there is no heap data.
         */
        ~ASTNumberExprNode();
        /**
         * The setter method used to give a value to the private variable this->value
         * @param value
         * The double value that will be stored in this->value
         */
        void setValue(double value);
        /**
         * A getter method used to get the value from the private variable this->value
         * @return
         * The double value stored in this->value
         */
        double getValue();
        /**
         * The implementation of the inherited virtual method from the parent
         * @param v
         * Stored a pointer to a visitor that is visiting this node.
         */
        void accept(Visitor *v) override;

        /**
         * This method is used to give a value to the private variable type
         * @param type
         * Stores the value of type number type to be assigned to the private variable this->numberType
         */
        void setNumberType(numberType type);
        /**
         * This method is used to return the value stored in number type
         * @return
         * A value of type numberType stored in numberType.
         */
        numberType getNumberType();
    private:
        double value; //Stores the value of the literal in the expression
        numberType type; // stores whether the value is a real or int , used in visitor classes.
    };
}


#endif //COMPILERSASSIGNMENT_ASTNUMBEREXPRNODE_H
