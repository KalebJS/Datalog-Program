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
    DatalogProgram datalog;
    std::queue<Token*> tokens;
    std::string result;
public:
    std::queue<Token*> FilterComments (std::vector<Token*> unfilteredTokens);
    bool Parse(std::vector<Token*> tokenVector);
    void VerifyToken (TokenType type);
    void VerifyToken (TokenType type, Predicate& predicate);
    void VerifyToken (TokenType type, Rule& rule);
    bool CompareNextTokenTypes (Token* token, TokenType type);
    void SchemeList ();
    void FactList ();
    void RuleList ();
    void QueryList ();
    void Scheme ();
    void Fact ();
    void RuleMethod ();
    void Query ();
    void HeadPredicate ();
    void HeadPredicate (Rule& rule);
    void PredicateMethod ();
    void PredicateMethod (Predicate& predicate);
    void PredicateMethod (Rule& rule);
    void PredicateList ();
    void PredicateList (Rule& rule);
    void ParameterList ();
    void ParameterList (Predicate& predicate);
    void StringList ();
    void StringList (Predicate& predicate);
    void IDList ();
    void IDList (Predicate& predicate);
    void Parameter ();
    void Parameter (Predicate& predicate);
    DatalogProgram GetDatalog () { return datalog; }
    std::string GetResult () { return result; }
};

#endif
