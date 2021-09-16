#ifndef LEXER_H
#define LEXER_H
#include <vector>
#include "Automaton.h"
#include "Token.h"

class Lexer
{
private:
    std::vector<Automaton*> automata;


    void CreateAutomata();

    // TODO: add any other private methods here (if needed)

public:
    Lexer();
    ~Lexer();
    std::vector<Token*> tokens;
    void Run(std::string& input);
    
    // TODO: add other public methods here

};

#endif // LEXER_H

