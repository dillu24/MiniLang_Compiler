//
// Created by Dylan Galea on 06/04/2018.
//

/**
 * This class is used to encode the Block statement node , which is created whenever the parser succesfully matches
 * the production rule related to the Block statement . This is a concrete child of ASTStatementNode thus it has the
 * getter,setter and variable statementType related to the enum StatementType along with the accept virtual method . Each
 * Block statement has a vector of statement nodes . I.e it has a list of children attached to it which are statements that
 * make up the block . Since this was declared as private , more getters and setters were designed .
 */

#ifndef COMPILERSASSIGNMENT_ASTBLOCKNODE_H
#define COMPILERSASSIGNMENT_ASTBLOCKNODE_H

#include <vector>
#include "../ASTStatementNode.h"
using namespace std;

namespace AST{
    class ASTBlockStatementNode:public ASTStatementNode {
    private:
        vector<ASTStatementNode*> *statements; //stores a list of statement children
    public:
        /**
         * The constructor used to create a new Block statement node having the children statements passed as param
         * @param statements
         * @param statements
         * Stores the adress the children statements that will be attached to the Block statement node
         */
        explicit ASTBlockStatementNode(vector<ASTStatementNode*>* statements);
        /**
         * The destructor used to remove data related with the ASTBlockStatementNode from the heap
         */
        ~ASTBlockStatementNode();
        /**
         * This method adds a statement as a child branch to the ASTBlockStatementNode
         * @param statement
         * The parameter that will be added to this->statements
         */
        void addStatement(ASTStatementNode* statement);
        /**
         * This method is used as a getter to get the private vector this->parameters
         * @return
         * a vector storing the children attached to ASTBlockStatementNodes
         */
        vector<ASTStatementNode*>* getStatements();
        /**
         * The implementation of the virtual accept method
         * @param v
         * Stores the address of the visitor that will visit this node
         */
        void accept(Visitor *v) override ;
    };
}


#endif //COMPILERSASSIGNMENT_ASTBLOCKNODE_H
