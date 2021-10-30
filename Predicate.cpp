#include <iostream>
#include "Predicate.h"

Predicate::Predicate() {
}

Predicate::~Predicate() {}

std::string Predicate::toString() {
    std::string predicateStr = id + '(';
    for (long unsigned int i = 0; i < parameters.size(); i++) {
        predicateStr += parameters.at(i).GetValue();
        if (i != parameters.size() - 1) {
            predicateStr += ",";
        }
    }
    predicateStr += ')';
    return predicateStr;
}

void Predicate::AddParameter(Token *token) {
    Parameter parameter = Parameter(token);
    parameters.push_back(parameter);
}

void Predicate::SetId(Token *token) {
    id = token->GetDescription();
}