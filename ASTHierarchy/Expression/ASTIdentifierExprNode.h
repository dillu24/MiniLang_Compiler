//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTIDENTIFEREXPRNODE_H
#define COMPILERSASSIGNMENT_ASTIDENTIFEREXPRNODE_H

#include "../ASTExprNode.h"
#include <string>
using namespace std;

namespace AST{
    class ASTIdentifierExprNode:public ASTExprNode {
    private:
        string identifierName;
    public:
        ASTIdentifierExprNode();
        explicit ASTIdentifierExprNode(string identifier);
        void setIdentifierName(string value);
        string getIdentifierName();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTIDENTIFEREXPRNODE_H
