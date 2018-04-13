//
// Created by Dylan Galea on 14/03/2018.
//

#ifndef COMPILERSASSIGNMENT_STATE_H
#define COMPILERSASSIGNMENT_STATE_H

/**
 * This enum class is used to encode the states of the DFSA representing the syntax of MINI LANG , in this enum
 * class 14 states were needed . See diagram of DFSA in documentation. Note there is a state SE which is used
 * whenever the transition function cannot find the state it needs to transition , and a BAD state. Both are used
 * for bad input.
 */

namespace Lexer{
    enum class State{
        S0,
        S1,
        S2,
        S3,
        S4,
        S5,
        S6,
        S7,
        S8,
        S9,
        S10,
        S11,
        S12,
        S13,
        S14,
        S15,
        SE,
        BAD
    };
}

#endif //COMPILERSASSIGNMENT_STATE_H
