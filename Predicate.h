#ifndef PREDICATE_H
#define PREDICATE_H

#include <string>
#include <vector>
#include "Token.h"

class Predicate {
private:
    std::vector<Token> elements;
public:
    Predicate();
    ~Predicate();
    std::string toString ();
    void AddElement (Token token);
    std::vector<Token> GetElements () { return elements; }
};

#endif
