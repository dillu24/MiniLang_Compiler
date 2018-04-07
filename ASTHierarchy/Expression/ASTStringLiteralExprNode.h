//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
#define COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
#include <string>
#include "../ASTExprNode.h"
using namespace std;
namespace AST{
    class ASTStringLiteralExprNode:public ASTExprNode {
    private:
        string sentence;
    public:
        explicit ASTStringLiteralExprNode(string sentence);
        void setSentence(string sentence);
        string getSentence();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTSTRINGLITERALEXPRNODE_H
