//
// Created by Dylan Galea on 19/03/2018.
//

#include "Keywords.h"

Lexer::Keywords::Keywords() {
    KeywordsList.insert("real");
    KeywordsList.insert("int");
    KeywordsList.insert("bool");
    KeywordsList.insert("string");
    KeywordsList.insert("true");
    KeywordsList.insert("false");
    KeywordsList.insert("and");
    KeywordsList.insert("or");
    KeywordsList.insert("not");
    KeywordsList.insert("set");
    KeywordsList.insert("var");
    KeywordsList.insert("print");
    KeywordsList.insert("return");
    KeywordsList.insert("if");
    KeywordsList.insert("else");
    KeywordsList.insert("while");
    KeywordsList.insert("def");
}

set<string> *Lexer::Keywords::getKeywordsList() {
    return &KeywordsList;
}
