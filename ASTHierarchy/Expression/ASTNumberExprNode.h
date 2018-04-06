//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTNUMBEREXPRNODE_H
#define COMPILERSASSIGNMENT_ASTNUMBEREXPRNODE_H

#include "../ASTExprNode.h"

namespace AST{
    class ASTNumberExprNode:ASTExprNode {
    private:
        double value;
    public:
        explicit ASTNumberExprNode(double val);
        ~ASTNumberExprNode();
        void setValue(double value);
        double getValue();
        void accept(Visitor *v) override;
    };
}


#endif //COMPILERSASSIGNMENT_ASTNUMBEREXPRNODE_H
