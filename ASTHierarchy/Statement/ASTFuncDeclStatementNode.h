//
// Created by Dylan Galea on 06/04/2018.
//

#ifndef COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H
#define COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H

#include "../ASTStatementNode.h"
#include "../Type.h"
#include "ASTBlockStatementNode.h"
#include "FormalParams.h"
#include <string>
using namespace std;

namespace AST{
    class ASTFuncDeclStatementNode:public ASTStatementNode {
    private:
        ASTIdentifierExprNode *identifier;
        FormalParams *fp;
        Type type;
        ASTBlockStatementNode *block;
    public:
        ASTFuncDeclStatementNode(AST::ASTIdentifierExprNode *identifier,FormalParams *fp,Type type,ASTBlockStatementNode *block);
        ~ASTFuncDeclStatementNode();
        void setIdentifier(ASTIdentifierExprNode* ident);
        void setFormalParams(FormalParams *fp);
        void setType(Type type);
        void setBlock(ASTBlockStatementNode *block);
        ASTIdentifierExprNode* getIdentifier();
        FormalParams* getFormalParams();
        Type getType();
        ASTBlockStatementNode* getBlock();
        void accept(Visitor *v) override;
    };
}

#endif //COMPILERSASSIGNMENT_ASTFUNCDECLSTATEMENTNODE_H
