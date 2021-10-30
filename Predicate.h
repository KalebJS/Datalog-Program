#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include "Token.h"
#include "Parameter.h"

class Predicate {
private:
    std::string id;
    std::vector<Parameter> parameters;
public:
    Predicate();

    ~Predicate();

    std::string toString();

    void AddParameter(Token *token);

    void SetId(Token *token);

    std::string GetId() { return id; }

    std::vector<Parameter> GetParameters() { return parameters; }
};

#endif
