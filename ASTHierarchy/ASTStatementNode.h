//
// Created by Dylan Galea on 04/04/2018.
//

/**
 * This class is a virtual child class of ASTNode thus it contains the accept method ,however still virtual since this
 * accept method will be implemented in concrete classes . This branch was needed in order to differ between expressions
 * and statement . Similar to the expression class , this class has an enum which gives the statement type in order to
 * avoid type casting in the visitor classes.
 **/

#ifndef COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H

#include "ASTNode.h"

using namespace AST;
namespace AST{
    class ASTStatementNode : public ASTNode {
    public:
        /**
         * As mentioned this enum type will be used to identify the type of the statement node the visitor is visiting
         * , since he can only view a list of statement nodes.
         */
        enum StatementType{
            ASSIGN_STMT,
            BLOCK_STMT,
            FUNC_DECL_STMT,
            IF_STMT,
            PRINT_STMT,
            RETURN_STMT,
            VAR_DECL_STMT,
            WHILE_STMT
        };

        /**
         * The accept method inherited from class ASTNode , here it is not implemented since ASTExprNode is a virtual
         * class
         * @param v
         * A pointer to a visitor that is going to visit the node.
         */
        void accept(Visitor *v) override = 0;
        /**
         * This method is used to give the protected statementType a value
         * @param type
         * Stores the type value that will be given to expressionType.
         */
        void setStatementType(StatementType type);
        /**
         * A getter method used to get the value in the protected variable statementType
         * @return
         * The value in expressionType
         */
        StatementType getStatementType();
    protected:
        StatementType statementType; //Stores the statement type
    };
}


#endif //COMPILERSASSIGNMENT_ASTSTATEMENTNODE_H
