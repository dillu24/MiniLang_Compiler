//
// Created by Dylan Galea on 06/04/2018.
//

/**
 * This enum class is used to encode the different types of the Minilang programming language. This will be used for
 * example in the ASTFuncDeclrStatementNode to store the type return of the function . Again an AST node could have been
 * created for this , however in order to avoid having lot of nodes this was declared as an enum class.
 **/

#ifndef COMPILERSASSIGNMENT_TYPE_H
#define COMPILERSASSIGNMENT_TYPE_H

namespace AST{
    enum class Type {
        REAL,
        INT,
        BOOL,
        STRING
    };
}


#endif //COMPILERSASSIGNMENT_TYPE_H
