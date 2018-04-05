//
// Created by Dylan Galea on 04/04/2018.
//
#ifndef COMPILERSASSIGNMENT_VISITOR_H
#define COMPILERSASSIGNMENT_VISITOR_H


#include "../ASTHierarchy/ASTExprNode.h"
#include "../ASTHierarchy/ASTStatementNode.h"

using namespace ASTHierarchy;

namespace Visitors{
    class Visitor {
    public:
        virtual void visit(ASTNode *node)=0;
        virtual void visit(ASTStatementNode *node)=0;
        virtual void visit(ASTExprNode *node)=0;
    };
}


#endif //COMPILERSASSIGNMENT_VISITOR_H
