//
// Created by Dylan Galea on 14/04/2018.
//

#include "SymbolTable.h"

Visitors::SymbolTable::SymbolTable() {
    contents = multimap<string,TypeBinder>();
}

void Visitors::SymbolTable::addToSymbolTable(string identifier, Visitors::TypeBinder type) {
    contents.insert(std::pair<string,TypeBinder>(identifier,type)); //insert a whole pair in the hash map
}

bool Visitors::SymbolTable::checkIfInSymbolTable(string identifier,TypeBinder::IdentifierType identifierType) {
    typedef std::multimap<string,TypeBinder>::iterator iterator1; //create an iterator type of the map
    std::pair<iterator1,iterator1> answers = contents.equal_range(identifier); //get the range of values of the mapped key value
    for(auto iterator = answers.first;iterator != answers.second;iterator++){
        if(iterator->second.getIdentifierType() == identifierType){ //if we find a mapped value of type given in identifierType
            return true;                                            // we have found such a pair
        }
    }
    return false; // if we do not find such a pair.
}

Visitors::TypeBinder Visitors::SymbolTable::getTypeBinder(string identifier) {
    return contents.find(identifier)->second;
}
