//
// Created by Kaleb Smith on 9/28/21.
//

#ifndef PARAMETER_H
#define PARAMETER_H

#include <string>
#include "Token.h"

enum class ParameterType {
    STRING,
    ID
};

class Parameter {
private:
    ParameterType type;
    std::string value;
public:
    Parameter(Token *token);

    ~Parameter();

    std::string TokenTypeToString(ParameterType parameterType);

    std::string ToString();

    std::string GetValue() { return value; }

    ParameterType GetType() { return type; }
};


#endif //PARAMETER_H
