#include "IdentifiersAutomaton.h"

void IdentifiersAutomaton::S0(const std::string &input) {
    if (isalpha(input[index])) {
        inputRead++;
        index++;
        S1(input);
    } else {
        Serr();
    }
}

void IdentifiersAutomaton::S1(const std::string &input) {
    if (isalpha(input[index]) || isdigit(input[index])) {
        inputRead++;
        index++;
        S1(input);
    }
}