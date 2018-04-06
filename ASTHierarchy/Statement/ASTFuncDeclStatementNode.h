//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "Type.h"
#include "ASTBlockStatementNode.h"
#include <string>
using namespace std;

namespace AST{
    class ASTFuncDeclStatementNode:ASTStatementNode {
    private:
        string identifier;
        Type type;
        ASTBlockStatementNode *block;
    public:
    };
}

#endif //COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H
