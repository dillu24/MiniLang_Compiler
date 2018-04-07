//
// Created by Dylan Galea on 07/04/2018.
//

#ifndef COMPILERSASSIGNMENT_FORMALPARAMS_H
#define COMPILERSASSIGNMENT_FORMALPARAMS_H

#include <vector>
#include "FormalParam.h"

namespace AST{
    class FormalParams {
    private:
        FormalParam *formalParam;
    public:
        vector<FormalParam*> parameters;
        explicit FormalParams(FormalParam *fp);
        ~FormalParams();
        void setFormalParam(FormalParam *fp);
        FormalParam* getFormalParam();
    };
}

#endif //COMPILERSASSIGNMENT_FORMALPARAMS_H
