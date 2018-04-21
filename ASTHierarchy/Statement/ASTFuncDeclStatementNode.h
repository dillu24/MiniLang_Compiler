//
// Created by Dylan Galea on 06/04/2018.
//

/**
 * This class is used to encode the AST function declaration expression node, which is created whenever the parser successfully
 * matching the production rule related to the function declaration . This node is a child of the statement node thus
 * it contains the setter,getter,statementType related to the enum statementType and the accept virtual method inherited
 * from the parent classes. This class also has as children an identifier expression node which stores the name of the
 * function just defined and a block statement node which stores the statements that make up the block . This class also
 * stores as information the type of the function and the parameters that must be passed to the function.
 */

#ifndef COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../Type.h"
#include "ASTBlockStatementNode.h"
#include "FormalParams.h"
#include <string>
using namespace std;

namespace AST{
    class ASTFuncDeclStatementNode:public ASTStatementNode {
    private:
        ASTIdentifierExprNode *identifier; //Stores the address of the identifier node storing the function name
        FormalParams *fp; // Stores a pointer to the parameters that make up the function definition
        Type type; // Stores the return type of the function
        ASTBlockStatementNode *block; //Stores an adress to the statements that make up the function
    public:
        /**
         * This constructor is used to create a new ASTFuncDeclStatementNode initializing all the children and relevant
         * information to the node in the process.
         * @param identifier
         * Stores the address of the identifier expression node that will be attached as child to this node
         * @param fp
         * Stores the address to the parameters that define the expression
         * @param type
         * Stores the return type of the function that will be assigned to this->type
         * @param block
         * Stores the adress of the block node that will be attached as child to this node
         */
        ASTFuncDeclStatementNode(AST::ASTIdentifierExprNode *identifier,FormalParams *fp,Type type,ASTBlockStatementNode *block);
        /**
         * The destructor used to remove data related to the function declaration statement from the heap
         */
        ~ASTFuncDeclStatementNode();
        /**
         * This setter is used to give values to the private variable this->identifier
         * @param ident
         * Stores the address of the identifier expression node that will be attached to this node
         */
        void setIdentifier(ASTIdentifierExprNode* ident);
        /**
         * This setter is used to give values to the private variable this->formalParams
         * @param fp
         * Stores the address of the parameters that will be stored in this->formalParams
         */
        void setFormalParams(FormalParams *fp);
        /**
         * This method is used to give values to this->type
         * @param type
         * Stores the type value of the function return value,that will be assigned to this->type
         */
        void setType(Type type);
        /**
         * This setter method is used to give this->block the address of the attached child block
         * @param block
         * Stores the adress of the block that will be assigned to this->block
         */
        void setBlock(ASTBlockStatementNode *block);
        /**
         * A getter used to get the value in this->identifier
         * @return
         * An ASTIdentifierExprNode pointer that stores the address of this->identifier
         */
        ASTIdentifierExprNode* getIdentifier();
        /**
         * A getter used to get the parameters that define the function
         * @return
         * A FormalParams pointer which stores the address of the parameters defining the function
         */
        FormalParams* getFormalParams();
        /**
         * A getter used to return the value in the private variable this->type
         * @return
         * The value of type Type in this->type
         */
        Type getType();
        /**
         * A getter used to return the value in this->block
         * @return
         * A pointer that stores the address of the child block attached to this node
         */
        ASTBlockStatementNode* getBlock();
        /**
         * This contains the implementation of the virtual method that was inherited from previous parents
         * @param v
         * Stores the address of the visitor visiting this node.
         */
        void accept(Visitor *v) override;
        /**
         * Used by the visitor function to print the type character representation.
         */
        void printType();

    };
}

#endif //COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H
