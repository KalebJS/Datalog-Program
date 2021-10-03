#include <iostream>
#include "Predicate.h"

Predicate::Predicate() {
}
Predicate::~Predicate() {
}
std::string Predicate::toString () {
    std::string predicateStr = "";
    for (long unsigned int i = 0; i < elements.size(); i++) {
        predicateStr += elements.at(i).GetDescription();
    }
    return predicateStr;
}
void Predicate::AddElement (Token token) {
    elements.push_back(token);
}