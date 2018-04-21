//
// Created by Dylan Galea on 20/04/2018.
//

/**
 * This class is used whenever the Lexer , Parser ,semantic analyzer or interpreter executor finds some error in the
 * program . Whenever such an error happens , the error message is saved in the class , so that it can be returned to
 * the programmer to see what is wrong with the program . Only one exception class was made since all errors have the
 * same fields and methods so they would be redundant since the user only wants the error message if he has done something
 * wrong.
 */

#ifndef COMPILERSASSIGNMENT_COMPILINGERROR_H
#define COMPILERSASSIGNMENT_COMPILINGERROR_H

#include <string>
using namespace std;

namespace Exception{
    class CompilingErrorException : public std::exception {
    private :
        string errorMessage; // stores the error message that cause the error
    public :
        /**
         * This is the constructor used to create a new instance of the CompilingErrorException initializing the
         * error message to @param message
         * @param message
         * Stores the error message to be assigned to this->errorMessage
         */
        explicit CompilingErrorException(string message);
        /**
         * This method is used to return the value in the private variable this->errorMessage
         * @return
         * A string value which is store in this->errorMessage
         */
        string getErrorMessage();
    };
}

#endif //COMPILERSASSIGNMENT_COMPILINGERROR_H
