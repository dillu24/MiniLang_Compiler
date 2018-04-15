//
// Created by Dylan Galea on 14/04/2018.
//

#include "SymbolTable.h"

Visitors::SymbolTable::SymbolTable() {
    contents = multimap<string,TypeBinder>();
}

void Visitors::SymbolTable::addToSymbolTable(string identifier, Visitors::TypeBinder type) {
    contents.insert(std::pair<string,TypeBinder>(identifier,type));
}

bool Visitors::SymbolTable::checkIfInSymbolTable(string identifier,TypeBinder::IdentifierType identifierType) {
    typedef std::multimap<string,TypeBinder>::iterator iterator1;
    std::pair<iterator1,iterator1> answers = contents.equal_range(identifier);
    for(auto iterator = answers.first;iterator != answers.second;iterator++){
        if(iterator->second.getIdentifierType() == identifierType){
            return true;
        }
    }
    return false;
}

Visitors::TypeBinder Visitors::SymbolTable::getTypeBinder(string identifier) {
    return contents.find(identifier)->second;
}
