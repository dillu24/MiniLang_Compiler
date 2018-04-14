//
// Created by Dylan Galea on 14/04/2018.
//

#ifndef COMPILERSASSIGNMENT_SYMBOLTABLE_H
#define COMPILERSASSIGNMENT_SYMBOLTABLE_H

#include <map>
#include "TypeBinder.h"

namespace Visitors{
    class SymbolTable {
    private:
        map<string,TypeBinder> contents;
    public:
        SymbolTable();
        void addToSymbolTable(string identifier , TypeBinder type);
        bool checkIfInSymbolTable(string identifier);
        TypeBinder getTypeBinder(string identifier);
    };
}

#endif //COMPILERSASSIGNMENT_SYMBOLTABLE_H
