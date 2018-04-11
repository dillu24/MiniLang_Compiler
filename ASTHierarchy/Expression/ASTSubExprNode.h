//
// Created by Dylan Galea on 07/04/2018.
//

/**
 * This class is used to encode an AST sub expression node that is created whenever a sub expression is identified using
 * the EBNF in the specification sheet by the parser. This class is a concrete child class of ASTExprNode thus it contains
 * the getter,setter,expressionType variable related to the enum ExpressionType and must implement the accept method.
 * An ASTSubExprNode has a child of type ASTExprNode that stores the expression in the sub expression. This expression
 * is declared as private and thus appropiate getters and setters had to be designed.
 */

#ifndef COMPILERSASSIGNMENT_ASTSUBEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTSUBEXPRNODE_H

#include "../ASTExprNode.h"

namespace AST{
    class ASTSubExprNode:public ASTExprNode {
    private:
        ASTExprNode* expression; //Stores the address of the ASTExprNode that is attached as a child to the sub expr node.
    public:
        /**
         * The constructor used to create a new ASTSubExprNode having child @param exp
         * @param exp
         * Stores a pointer to an ASTExprNode that will be attached to the ASTSubExprNode
         */
        explicit ASTSubExprNode(ASTExprNode* exp);
        /**
         * Destructor used to remove data related to the ASTSubExprNode from the heap
         */
        ~ASTSubExprNode();
        /**
         * This method is used to give a value to the private variable this->expression*
         * @param expr
         * Stores a pointer to an ASTExprNode that will be assigned to this->expression*
         */
        void setSubExpr(ASTExprNode* expr);
        /**
         * This getter is used to get the this->expression pointer
         * @return
         * An ASTExprNode*
         */
        ASTExprNode* getSubExpr();
        /**
         * The implementation of the inherited virtual accept function
         * @param v
         * Stores a pointer to a visitor that is visiting an ASTSubExprNode
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTSUBEXPRNODE_H
