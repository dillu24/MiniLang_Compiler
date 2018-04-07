//
// Created by Dylan Galea on 07/04/2018.
//

#include "FormalParams.h"

AST::FormalParams::FormalParams(AST::FormalParam *fp) {
    formalParam = &*fp;
    parameters = vector<FormalParam*>();
}

AST::FormalParams::~FormalParams() {
    delete formalParam;
    for(unsigned int i=0;i<parameters.size();i++){
        delete parameters.at(i);
    }
}

void AST::FormalParams::setFormalParam(AST::FormalParam *fp) {
    formalParam = &*fp;
}

AST::FormalParam *AST::FormalParams::getFormalParam() {
    return formalParam;
}
