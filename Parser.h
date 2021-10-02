#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "DatalogProgram.h"
#include "Predicate.h"
#include "Rule.h"
#include <vector>
#include <queue>

class Parser {
private:
    DatalogProgram* datalog;
    std::queue<Token*> tokens;
public:
    std::queue<Token*> FilterComments (std::vector<Token*> unfilteredTokens);
    void Parse(std::vector<Token*> tokenVector);
    void VerifyToken (TokenType type);
    bool CompareNextTokenTypes (Token* token, TokenType type);
    void SchemeList ();
    void FactList ();
    void RuleList ();
    void QueryList ();
    void Scheme ();
    void Fact ();
    void Rule ();
    void Query ();
    void HeadPredicate ();
    void Predicate ();
    void PredicateList ();
    void ParameterList ();
    void StringList ();
    void IDList ();
    void Parameter ();
    DatalogProgram* GetDatalog () { return datalog; }
};

#endif
