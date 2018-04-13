//
// Created by Dylan Galea on 07/04/2018.
//

/**
 *This class encodes an enum class for the negation operators , this is used in the ASTUnaryExprNode to store the operator
 * in front of the expression stored also in the ASTUnaryExprNode.This could have been done by implemented another AST
 * node for the negation operators , but in order to not create too much nodes , an enum class was done.
 **/

#ifndef COMPILERSASSIGNMENT_NEGATIONOPERATOR_H
#define COMPILERSASSIGNMENT_NEGATIONOPERATOR_H

namespace AST{
    enum class NegationOperator {
        NOT,
        MINUS
    };
}

#endif //COMPILERSASSIGNMENT_NEGATIONOPERATOR_H
