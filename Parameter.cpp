//
// Created by Kaleb Smith on 9/28/21.
//

#include "Parameter.h"


Parameter::Parameter(Token *token) {
    if (token->GetTokenType() == TokenType::ID) {
        type = ParameterType::ID;
    } else if (token->GetTokenType() == TokenType::STRING) {
        type = ParameterType::STRING;
    }
    value = token->GetDescription();
}

Parameter::~Parameter() {}

std::string Parameter::TokenTypeToString(ParameterType parameterType) {
    switch (parameterType) {
        case ParameterType::ID:
            return "ID";
            break;
        case ParameterType::STRING:
            return "STRING";
            break;
        default:
            return "";
            break;
    }
}

std::string Parameter::ToString() {
    return '(' + TokenTypeToString(type) + ", " + value + ')';
}

