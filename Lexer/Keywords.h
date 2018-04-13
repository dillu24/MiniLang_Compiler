//
// Created by Dylan Galea on 19/03/2018.
//

#ifndef COMPILERSASSIGNMENT_KEYWORDS_H
#define COMPILERSASSIGNMENT_KEYWORDS_H

#include <iostream>
#include <set>

/**
 * This class is used to act as a look up for keyword that are important to MINI_LANG. In fact this class has a set
 * of keywords which cannot be edited, only retrieved.
 */

using namespace std;
namespace Lexer{
    class Keywords {
    private:
        set<string> KeywordsList; //Stores the keywords of mini lang
    public :
        /**
         * Constructor used to initialize the keyword set
         */
        Keywords();
        /**
         * Used as a getter to get the private set KeywordsList
         * @return
         * A pointer to the keywords list.
         */
        set<string>* getKeywordsList();
    };
}


#endif //COMPILERSASSIGNMENT_KEYWORDS_H
