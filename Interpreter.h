//
// Created by Kaleb Smith on 10/23/21.
//

#ifndef DATALOG_INTERPRETER_H
#define DATALOG_INTERPRETER_H


#include "DatalogProgram.h"

class Interpreter {
private:
    DatalogProgram *datalogProgram;
    Database *database;
public:
    Interpreter(DatalogProgram *datalogProgramPointer, Database *databasePointer);

    void Interpret();

    void InterpretSchemes();

    void InterpretFacts();

    void InterpretRules();

    void InterpretQueries();

    static std::vector<int> FindMatchingIds(std::vector<Parameter> parameters, const std::string &id);

    static void PrintQueryResult(Predicate query, Relation queryResult);
};


#endif //DATALOG_INTERPRETER_H
