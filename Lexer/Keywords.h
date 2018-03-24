//
// Created by Dylan Galea on 19/03/2018.
//

#ifndef COMPILERSASSIGNMENT_KEYWORDS_H
#define COMPILERSASSIGNMENT_KEYWORDS_H

#include <iostream>
#include <set>

using namespace std;
namespace Lexer{
    class Keywords {
    private:
        set<string> KeywordsList;
    public :
        Keywords();
        set<string>* getKeywordsList();
    };
}


#endif //COMPILERSASSIGNMENT_KEYWORDS_H
