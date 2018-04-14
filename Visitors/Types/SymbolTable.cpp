//
// Created by Dylan Galea on 14/04/2018.
//

#include "SymbolTable.h"

Visitors::SymbolTable::SymbolTable() {
    contents = map<string,TypeBinder>();
}

void Visitors::SymbolTable::addToSymbolTable(string identifier, Visitors::TypeBinder type) {
    if(contents.find(identifier) == contents.end()){
        contents.insert(std::pair<string,TypeBinder>(identifier,type));
    }
}

bool Visitors::SymbolTable::checkIfInSymbolTable(string identifier) {
    return !(contents.find(identifier) == contents.end());
}

Visitors::TypeBinder Visitors::SymbolTable::getTypeBinder(string identifier) {
    return contents.find(identifier)->second;
}
