#include "StringAutomaton.h"
#include <iostream>

void StringAutomaton::S0(const std::string& input) {
    if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
void StringAutomaton::S1(const std::string& input) {
    if (index == static_cast<int>(input.length())) {
        ToUndefinedType();
    }
    else if (input[index] == '\'') {
        inputRead++;
        index++;
        S2(input);
    }
    else {
        inputRead++;
        index++;
        S1(input);
    }
}
void StringAutomaton::S2(const std::string& input) {
    if (index == static_cast<int>(input.length())) {
        ToUndefinedType();
    }
    else if (input[index] == '\'') {
        inputRead++;
        index++;
        S1(input);
    }
}