//
// Created by Dylan Galea on 07/04/2018.
//

/**
 * This class encodes the node that will be created whenever the parser meets a Function call expression in the program
 * according to the bnf given in the specification sheet. Each ASTFnCallNode branches to an ASTIdentifierExpr node that
 * stores the identifier name of the function call , and to 0 or more parameters which are expression nodes . The
 * ASTFnCallExprNode is a child of the ASTExpr and since it is concrete , it must implement the accept virtual method
 * inherited from parent classes . It also contains the getter, setter and expressionType related to the ExpressionType
 * enum.
 */
#ifndef COMPILERSASSIGNMENT_ASTFNCALLEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTFNCALLEXPRNODE_H

#include <vector>
#include "ASTIdentifierExprNode.h"

namespace AST{
    class ASTFnCallExprNode:public ASTExprNode {
    private:
        ASTIdentifierExprNode* identifier; //stores a pointer to an ASTIdentifierExprNode that stores the identifier name of the fn
        vector<ASTExprNode*> parameters; // A list of 0 or more parameters passed to the fn.
    public:
        /**
         * This constructor is used to initialize a new ASTFnCallExprNode with the passed identifier as parameter,
         * and initializes by default the parameters list to be empty.
         * @param identifier
         * A pointer to the ASTIdentiferExprNode* that will be attached as children to the newASTFnCallExprNode
         */
        explicit ASTFnCallExprNode(ASTIdentifierExprNode* identifier);
        /**
         * This destructor is used to delete all data of the ASTFnCallExprNode from the heap
         */
        ~ASTFnCallExprNode();
        /**
         * This setter method is used to give the private "ASTIdentiferExprNode*" a value
         * @param identifier
         * Stores a pointer to an ASTIdentifierExprNode* that will be attached as a child to the ASTFnCallExprNode
         */
        void setIdentifier(ASTIdentifierExprNode* identifier);
        /**
         * A method used to add new parameters to the vector storing the parameters, i.e adding new ASTExprNode children
         * to the ASTFnCallExprNode
         * @param params
         * Stores a pointer to the  parameter of type ASTExprNode that will be attached as a child to the new ASTFnCall
         * ExprNode.
         */
        void addParameters(ASTExprNode* params);
        /**
         * This method is used to get the parameters that were passed to the function call
         * @return
         * A vector of type ASTExprNode* that represents the parameters that were passed to the function call
         */
        vector<ASTExprNode*> getParameters();
        /**
         * Gets the ASTIdentifierExpr private child attached to the ASTFnCallExprNode
         * @return
         * A pointer to an IdentifierExprNode that is attached as a child to ASTFnCallExprNode
         */
        ASTIdentifierExprNode* getIdentifier();
        /**
         * The implementation of this method that was virtual in the abstract parent classes.
         * @param v
         * Stores a pointer to a visitor that is going to visit the node.
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTFNCALLEXPRNODE_H
