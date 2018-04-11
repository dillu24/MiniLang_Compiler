//
// Created by Dylan Galea on 07/04/2018.
//
/**
 * This class is used to store the formal parameters of a function declaration which can be 0 or more . This class is
 * not part of the AST hierarchy and thus is only used as a form of type class in the ASTFuncDeclStatementNode ,since
 * it was not seen as important to create such node for the parse tree , since it does not effect the structure of the program
 */
#ifndef COMPILERSASSIGNMENT_FORMALPARAMS_H
#define COMPILERSASSIGNMENT_FORMALPARAMS_H

#include <vector>
#include "FormalParam.h"

namespace AST{
    class FormalParams {
    private:
        FormalParam *formalParam; //stores the first parameter in the parameters list
    public:
        vector<FormalParam*> parameters; //stores the remaining parameters in a vector , this was done this was to reflect
                                         // the EBNF structure
        /**
         * This constructor is used to create a new FormalParams object storing the value of @param fp in this->formalParam
         * @param fp
         */
        explicit FormalParams(FormalParam *fp);
        /**
         * This destructor is used to delete all FormalParams related data from the heap
         */
        ~FormalParams();
        /**
         * This setter is used to give a value to this->formalParam
         * @param fp
         * Stores the address of the FormalParam object to be assigned to this->formalParam
         */
        void setFormalParam(FormalParam *fp);
        /**
         * This getter is used to get the pointer this->formalParam
         * @return
         * The pointer this->formalParam
         */
        FormalParam* getFormalParam();
    };
}

#endif //COMPILERSASSIGNMENT_FORMALPARAMS_H
