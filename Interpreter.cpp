//
// Created by Kaleb Smith on 10/23/21.
//

#include "Interpreter.h"

Interpreter::Interpreter(DatalogProgram *datalogProgramPointer, Database *databasePointer) {
    datalogProgram = datalogProgramPointer;
    database = databasePointer;
}

void Interpreter::Interpret() {
    // Interpret the datalog program
    InterpretSchemes();
    InterpretFacts();
//    InterpretRules();
    InterpretQueries();
}

void Interpreter::InterpretSchemes() {
    // Iterate through the schemes
    for (long unsigned int i = 0; i < datalogProgram->getSchemes().size(); i++) {
        Predicate scheme = datalogProgram->getSchemes().at(i);
        // Add the scheme to the database
        database->AddRelation(scheme);
    }
}

void Interpreter::InterpretFacts() {
    // Iterate through the facts
    for (long unsigned int i = 0; i < datalogProgram->getFacts().size(); i++) {
        Predicate fact = datalogProgram->getFacts().at(i);
        // Add the fact to the database
        database->AddRelationParameters(fact);
    }
}

void Interpreter::InterpretQueries() {
    for (auto query: datalogProgram->getQueries()) {
        Relation queryResult = database->FindRelation(query.GetId());
        std::vector<Parameter> queryParameters = query.GetParameters();
        std::vector<int> variableIndices;
        for (long unsigned int i = 0; i < queryParameters.size(); i++) {
            if (queryParameters.at(i).GetType() == ParameterType::STRING) {
                queryResult = queryResult.Select((int) i, queryParameters.at(i).GetValue());
            } else if (queryParameters.at(i).GetType() == ParameterType::ID) {
                queryResult = queryResult.Select(FindMatchingIds(queryParameters, queryParameters.at(i).GetValue()));
                variableIndices.push_back((int) i);
                queryResult = queryResult.Rename((int) i, queryParameters.at(i).GetValue());
            }
        }
        queryResult = queryResult.Project(variableIndices);
        PrintQueryResult(query, queryResult);
    }
}

std::vector<int> Interpreter::FindMatchingIds(std::vector<Parameter> parameters, const std::string &id) {
    std::vector<int> matchingIndexes;
    for (long unsigned int i = 0; i < parameters.size(); i++) {
        if (parameters.at(i).GetType() == ParameterType::ID) {
            if (parameters.at(i).GetValue() == id) {
                matchingIndexes.push_back((int) i);
            }
        }
    }
    return matchingIndexes;
}

void Interpreter::PrintQueryResult(Predicate query, Relation queryResult) {
    std::cout << query.toString() << "?";
    int numTuples = queryResult.GetTuples().size();
    if (numTuples > 0) {
        std::cout << " Yes(" << numTuples << ")" << std::endl;
    } else {
        std::cout << " No" << std::endl;
    }
    for (auto tuple: queryResult.GetTuples()) {

        if (tuple.GetValues().size() > 0) {
            std::cout << "  ";
            for (long unsigned int j = 0; j < queryResult.GetHeader().GetParameters().size(); j++) {
                std::cout << queryResult.GetHeader().GetParameters().at(j) << "="
                          << tuple.GetValues().at(j);
                if (j < queryResult.GetHeader().GetParameters().size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }
}