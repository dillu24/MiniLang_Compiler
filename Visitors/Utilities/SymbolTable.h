//
// Created by Dylan Galea on 14/04/2018.
//
/**
 * This class is used to encode the Symbol Table that is used whenever a scoped is opened to store variables that are
 * related with that scope. Thus this class represents one table entry for a particular scope. A scope has a multimap
 * that stores the variable's and function's names which are mapped to an instance of a type binder. A multimap is used
 * instead of a map because , in this language it was assumed that we can have a function and a variable with the same
 * name , however we cannot have 2 functions and 2 variables with the same name .
 */
#ifndef COMPILERSASSIGNMENT_SYMBOLTABLE_H
#define COMPILERSASSIGNMENT_SYMBOLTABLE_H

#include <map>
#include "TypeBinder.h"

namespace Visitors{
    class SymbolTable {
    private:
        multimap<string,TypeBinder> contents; //Represents a hash map where the key is the identifier name and the mapped
                                              // value is an instance of type binder which stores information about that
                                              // identifier.Note 1 identifier can have a type binder related to a function
                                              // and another one related to a variable.
    public:
        /**
         * This method is used to create a new SymbolTable ,initializing memory to the vector 'contents'
         */
        SymbolTable();
        /**
         * This method is used to create an entry in the symbol table where the key is the identifier name and the
         * mapped value is the type binder instance.
         * @param identifier
         * Stores the name of the identifier to be added as key to the multimap
         * @param type
         * Stores the TypeBinder to be attached as mapped value to the multimap
         */
        void addToSymbolTable(string identifier , TypeBinder type);
        /**
         * This method is used to check if an identifier of some type function or variable is already found in the symbol
         * table
         * @param identifier
         * Stores the identifier name to be used as key to search the multimap
         * @param type
         * Stores whether we are searching to a mapped value that is a function or a variable
         * @return
         * True if such value is found , false otherwise.
         */
        bool checkIfInSymbolTable(string identifier,TypeBinder::IdentifierType type);
        /**
         * This method is used to get the mapped value attached to a passed by value key.
         * @param identifier
         * Stores the identifier name to be used as key in order to return the mapped value in the multimap
         * @return
         * The mapped value associated to the key stored in @param identifier , which is of type TypeBinder.
         */
        TypeBinder getTypeBinder(string identifier,TypeBinder::IdentifierType);

        /**
         * This method is used to get the private field multimap
         * @return
         * The private field multimap
         */
        multimap<string,TypeBinder> getMultimap();

    };
}

#endif //COMPILERSASSIGNMENT_SYMBOLTABLE_H
