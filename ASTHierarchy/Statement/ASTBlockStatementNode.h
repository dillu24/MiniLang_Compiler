//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTBLOCKNODE_H
#define COMPILERSASSIGNMENT_ASTBLOCKNODE_H

#include <vector>
#include "../ASTStatementNode.h"
using namespace std;

namespace AST{
    class ASTBlockStatementNode:ASTStatementNode {
    private:
        vector<ASTStatementNode*> *statements;
    public:
        explicit ASTBlockStatementNode(vector<ASTStatementNode*>* statements);
        ~ASTBlockStatementNode();
        void addStatement(ASTStatementNode* statement);
        vector<ASTStatementNode*>* getStatements();
        void removeStatement(int index);
        void accept(Visitor *v) override ;
    };
}


#endif //COMPILERSASSIGNMENT_ASTBLOCKNODE_H
