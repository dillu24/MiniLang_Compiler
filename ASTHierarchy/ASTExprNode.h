//
// Created by Dylan Galea on 04/04/2018.
//
/**
 * This class is used to encode the expression nodes ,it is a virtual child of ASTNode , thus it's concrete types
 * must implement the accept method . Also in order to avoid type casting in virtual classes , an enum giving the
 * expression type was created .
 **/

#ifndef COMPILERSASSIGNMENT_ASTEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTEXPRNODE_H

#include "ASTNode.h"
namespace AST {
    class ASTExprNode: public ASTNode {
    public:
        /**
         * This enum is used to identify what type the expression is . This is needed so that in the Visitor classes
         * we would know what type of node we are visiting , since the parse tree is a list of statements nodes only ,
         * hence avoid type casting.
         */
        enum ExpressionType {
            BINARY_EXP,
            BOOLEAN_LITERAL_EXP,
            FNCALL_EXP,
            IDENTIFIER_EXP,
            NUMBER_EXP,
            STRING_LITERAL_EXP,
            SUB_EXP,
            UNARY_EXP
        };

        /**
         * The accept method inherited from class ASTNode , here it is not implemented since ASTExprNode is a virtual
         * class
         * @param v
         * A pointer to a visitor that is going to visit the node.
         */
        void accept(Visitor *v) override = 0;
        /**
         * This getter is used to get the expression type in the children
         * @return
         * The expression type value of type ExpressionType
         */
        ExpressionType getExpressionType();
        /**
         * This setter is used to give a value of type ExpressionType to the expressionType variable
         * @param expressionType
         * stores the expression type value that will be assigned to expressionType;
         */
        void setExpressionType(ExpressionType expressionType);
    protected:
        ExpressionType expressionType; //stores the expression type
    };

}


#endif //COMPILERSASSIGNMENT_ASTEXPRNODE_H
