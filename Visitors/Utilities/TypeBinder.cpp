//
// Created by Dylan Galea on 14/04/2018.
//

#include "TypeBinder.h"

#include <utility>

Visitors::TypeBinder::TypeBinder(Type primitiveType, Visitors::TypeBinder::IdentifierType identifierType) {
    this->primitiveType = primitiveType;
    this->identifierType = identifierType;
    this->parameterTypes = vector<Type>();
    value = new valueInIdentifier();
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

void TypeBinder::setIntValue(int value) {
    this->value->intValue = value;
}

void TypeBinder::setRealValue(double value) {
    this->value->realValue = value;
}

void TypeBinder::setStringValue(string value) {
    this->value->stringValue = std::move(value);
}

void TypeBinder::setBoolValue(bool value) {
    this->value->boolValue = value;
}

TypeBinder::valueInIdentifier* TypeBinder::getValueInIdentifier() {
    return value;
}

void TypeBinder::setFnDefnBlock(ASTBlockStatementNode *value) {
    this->FnDefnBlock = &*value;
}

ASTBlockStatementNode *TypeBinder::getFnDefnBlock() {
    return FnDefnBlock;
}

void TypeBinder::setFormalParams(FormalParams *fp) {
    this->formalParams = &*fp;
}

FormalParams *TypeBinder::getFormalParams() {
    return formalParams;
}

string TypeBinder::getStringRepresentationOfIdentifierType() {
    if(identifierType == FUNCTION){
        return "function";
    }else{
        return "variable";
    }
}



