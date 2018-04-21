//
// Created by Dylan Galea on 20/04/2018.
//

#include "CompilingErrorException.h"

#include <utility>

Exception::CompilingErrorException::CompilingErrorException(string message) {
    this->errorMessage = std::move(message);
}

string Exception::CompilingErrorException::getErrorMessage() {
    return errorMessage;
}
