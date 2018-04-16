//
// Created by Dylan Galea on 14/04/2018.
//

#include "TypeBinder.h"

Visitors::TypeBinder::TypeBinder(Type primitiveType, Visitors::TypeBinder::IdentifierType identifierType) {
    this->primitiveType = primitiveType;
    this->identifierType = identifierType;
    this->parameterTypes = vector<Type>();
}

Type Visitors::TypeBinder::getPrimitiveType() {
    return primitiveType;
}

Visitors::TypeBinder::IdentifierType Visitors::TypeBinder::getIdentifierType() {
    return identifierType ;
}

void Visitors::TypeBinder::setIdentifierType(Visitors::TypeBinder::IdentifierType identifierType) {
    this->identifierType = identifierType;
}

void Visitors::TypeBinder::setPrimitiveType(Type type) {
    this->primitiveType = type;
}

string Visitors::TypeBinder::getStringRepresentationOfPrimitiveType() { //return the keyword related to each value of the enum
    switch(primitiveType){
        case Type::REAL:
            return "real";
        case Type::INT:
            return "int";
        case Type::BOOL:
            return "bool";
        case Type::STRING:
            return "string";
    }
}



