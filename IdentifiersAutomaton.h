#ifndef IDENTIFIERSAUTOMATON_H
#define IDENTIFIERSAUTOMATON_H

#include "Automaton.h"

class IdentifiersAutomaton : public Automaton
{
private:
    void S1 (const std::string& input);

public:
    IdentifiersAutomaton() : Automaton(TokenType::ID) {}  // Call the base constructor

    void S0(const std::string& input);
};

#endif // IDENTIFIERSAUTOMATON_H

