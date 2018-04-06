//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H

#include "../ASTExprNode.h"

namespace AST {
    class ASTBinaryExprNode:ASTExprNode {
    private:
        ASTExprNode *Lhs;
        ASTExprNode *Rhs;
        char op;
    public:
        ASTBinaryExprNode(ASTExprNode *left,ASTExprNode *right,char oper);
        ~ASTBinaryExprNode();
        void setLhs(ASTExprNode *left);
        void setRhs(ASTExprNode *right);
        ASTExprNode* getLhs();
        ASTExprNode* getRhs();
        void accept(Visitor *v) override;
    };
}


#endif //COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H
