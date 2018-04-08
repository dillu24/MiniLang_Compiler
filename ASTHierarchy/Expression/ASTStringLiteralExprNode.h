//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
#include <string>
#include "../ASTExprNode.h"
#include "ASTLiteralExprNode.h"

using namespace std;

namespace AST{
    class ASTStringLiteralExprNode:public ASTLiteralExprNode {
    private:
        string sentence;
    public:
        explicit ASTStringLiteralExprNode(string sentence);
        ~ASTStringLiteralExprNode();
        void setValue(string sentence);
        string getValue();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
