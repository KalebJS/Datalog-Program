#include "CommentAutomaton.h"
#include <iostream>

void CommentAutomaton::S0(const std::string& input) {
    if (input[index] == '#') {
        inputRead++;
        index++;
        S1(input);
    }
    else {
        Serr();
    }
}
void CommentAutomaton::S1(const std::string& input) {
    if (index == static_cast<int>(input.length())) {
        ToUndefinedType();
    }
    else if (input[index] == '|') {
        inputRead++;
        index++;
        S3(input);
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}
void CommentAutomaton::S2(const std::string& input) {
    if (index == static_cast<int>(input.length())) {
        ToUndefinedType();
    }
    else if (input[index] == '\n') {
        return;
    }
    else {
        inputRead++;
        index++;
        S2(input);
    }
}
void CommentAutomaton::S3(const std::string& input) {
    if (index == static_cast<int>(input.length())) {
        ToUndefinedType();
    }
    else if (input[index] == '|') {
        inputRead++;
        index++;
        S4(input);
    }
    else {
        inputRead++;
        index++;
        S3(input);
    }
}
void CommentAutomaton::S4(const std::string& input) {
    if (index == static_cast<int>(input.length())) {
        ToUndefinedType();
    }
    else if (input[index] == '#') {
        inputRead++;
    }
    else {
        inputRead++;
        index++;
        S3(input);
    }
}