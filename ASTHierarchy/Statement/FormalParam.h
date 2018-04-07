//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_FORMALPARAM_H
#define COMPILERSASSIGNMENT_FORMALPARAM_H

#include <string>
#include "../Type.h"
#include "../Expression/ASTIdentifierExprNode.h"

using namespace std;

namespace AST{
    class FormalParam {
    private:
        ASTIdentifierExprNode *identifier;
        Type type;
    public:
        FormalParam(ASTIdentifierExprNode *ident,Type type);
        void setIdentifier(ASTIdentifierExprNode *ident);
        void setType(Type type);
        ASTIdentifierExprNode* getIdentifier();
        Type getType();
    };
}
#endif //COMPILERSASSIGNMENT_FORMALPARAM_H
