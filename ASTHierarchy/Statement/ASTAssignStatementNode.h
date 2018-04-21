//
// Created by Dylan Galea on 06/04/2018.
//

/**
 * This class is used to encode the AST assign statement node , which is created whenever the parser matches succesfully
 * a production rule given by the specified EBNF related to assignment. This is a concrete child of ASTStatementNode and
 * thus must implement the accept function and contains the getter,setter and statementType variable related to the
 * enum StatementType. The ASTAssignStatementClass has 2 children , one is an ASTIdentifierExprNode that stores the
 * name of the identifier being assigned and the other is an ASTExprNode which stores the expression that the variable
 * is being assigned to. Since these were designed to be private , appropiate getters and setters had to be designed.
 */

#ifndef COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../ASTExprNode.h"
#include "../Expression/ASTIdentifierExprNode.h"
#include <string>
using namespace std;

namespace AST{
    class ASTAssignStatementNode: public ASTStatementNode {
    private:
        ASTIdentifierExprNode* identifier; //Stores the address of the ASTIdentifierExprNode storing the identifier name
        ASTExprNode* expression; //Stores the address of the node expression the identifier is assigned to
    public:
        /**
         * This constructor is used to initialize a new ASTAssignStatementNode assigning the values of @param ident,expr
         * to this->identifier,expression respectively , thus creating 2 children.
         * @param ident
         * Stores the address of the identifier node to be assigned to this->identifier
         * @param expr
         * Stores the address of the expression noe to be assigned to this->expression
         */
        ASTAssignStatementNode(ASTIdentifierExprNode* ident,ASTExprNode* expr);
        /**
         * The destructor used to remove data related to ASTAssignStatementNode from the heap
         */
        ~ASTAssignStatementNode();
        /**
         * The setter method used to give a value to this->identifier
         * @param identifier
         * Stores the identifier expression node value that will be assigned to this->identifier
         */
        void setIdentifier(ASTIdentifierExprNode* identifier);
        /**
         * The setter method used to give a value to this->expression
         * @param expr
         * Stores the expression node value that will be assigned to this->expression
         */
        void setExpression(ASTExprNode* expr);
        /**
         * A getter method used to get the value stored in this->expression
         * @return
         * A pointer of type ASTExprNode storing the address of the child expression node.
         */
        ASTExprNode* getExpression();
        /**
         * A getter method used to get the value stored in this->identifier
         * @return
         * A pointer of type ASTIdentifierExprNode storing the address of the child identifier node
         */
        ASTIdentifierExprNode* getIdentifier();
        /**
         * The implementation of the virtual accept method
         * @param v
         * Stores the address of the visitor that is visiting this node.
         */
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTASSIGNSTATEMENTNODE_H
