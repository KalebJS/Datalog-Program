//
// Created by Kaleb Smith on 9/28/21.
//

#ifndef DATALOGPROGRAM_H
#define DATALOGPROGRAM_H
#include "Predicate.h"
#include "Rule.h"
#include "Token.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

class DatalogProgram {
private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Predicate> queries;
    std::vector<Rule> rules;
    std::vector<std::string> domain;

public:
    DatalogProgram() {}
    ~DatalogProgram() {}
    void AddScheme (Predicate scheme) { schemes.push_back(scheme); }
    void AddFact (Predicate fact);
    void AddQuery (Predicate query) { queries.push_back(query); }
    void AddRule (Rule rule) { rules.push_back(rule); }

    std::string toString ();

};

#endif //DATALOGPROGRAM_H
