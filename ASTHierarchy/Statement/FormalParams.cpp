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
    for (auto &parameter : parameters) {
        delete parameter;
    }
}

void AST::FormalParams::setFormalParam(AST::FormalParam *fp) {
    formalParam = &*fp;
}

AST::FormalParam *AST::FormalParams::getFormalParam() {
    return formalParam;
}
