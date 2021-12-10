//
// Created by Kaleb Smith on 10/23/21.
//

#ifndef DATALOG_INTERPRETER_H
#define DATALOG_INTERPRETER_H


#include "DatalogProgram.h"
#include "StronglyConnectedComponent.h"
#include "Graph.h"

class Interpreter {
private:
    DatalogProgram *datalogProgram;
    Database *database;
    unsigned ruleEvaluations = 1;
    std::vector<StronglyConnectedComponent> sccs;
public:
    Interpreter(DatalogProgram *datalogProgramPointer, Database *databasePointer);

    void Interpret();

    void InterpretSchemes();

    void InterpretFacts();

    void FindStronglyConnectedComponents();

    void InterpretRules();

    void InterpretQueries();

    static std::vector<int> FindMatchingIds(std::vector<Parameter> parameters, const std::string &id);

    static void PrintQueryResult(Predicate query, Relation *queryResult);

    static void PrintRuleResult(Rule rule, Relation *queryResult);
};


#endif //DATALOG_INTERPRETER_H
