//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H

#include "../ASTExprNode.h"
#include "../Operators.h"

namespace AST {
    class ASTBinaryExprNode:public ASTExprNode {
    private:
        ASTExprNode *Lhs;
        ASTExprNode *Rhs;
        Operators op;
    public:
        ASTBinaryExprNode(ASTExprNode *left,ASTExprNode *right,Operators oper);
        ~ASTBinaryExprNode();
        void setLhs(ASTExprNode *left);
        void setRhs(ASTExprNode *right);
        void setOperator(Operators op);
        ASTExprNode* getLhs();
        ASTExprNode* getRhs();
        Operators getOperator();
        void accept(Visitor *v) override;
    };
}


#endif //COMPILERSASSIGNMENT_ASTBINARYEXPRNODE_H
