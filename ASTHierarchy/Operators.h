//
// Created by Dylan Galea on 07/04/2018.
//

/**
 * This enum class stores the operators that will be used in the expressions , these will be used in order to store
 * which type of operation is present in the ASTBinaryExprNode and ASTSubExprNode . An alternative implementation could
 * have been done where the operators would be considered as nodes , however this was not done this way in order to
 * avoid having too much nodes in the AST .
 **/

#ifndef COMPILERSASSIGNMENT_ADDITIVEOPERATORS_H
#define COMPILERSASSIGNMENT_ADDITIVEOPERATORS_H

namespace AST{
    enum class Operators{
        PLUS,
        MINUS,
        OR,
        LESSTHAN,
        GREATERTHAN,
        LESSTHANEQUAL,
        GREATERTHANEQUAL,
        EQUALTO,
        NOTEQUAL,
        TIMES,
        DIVISION,
        AND
    };
}

#endif //COMPILERSASSIGNMENT_ADDITIVEOPERATORS_H
