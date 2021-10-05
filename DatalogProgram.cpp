//
// Created by Kaleb Smith on 9/28/21.
//

#include "DatalogProgram.h"

void DatalogProgram::AddFact(Predicate fact)  {
    facts.push_back(fact);
    for (long unsigned int i = 0; i < fact.GetElements().size(); i++) {
        if (fact.GetElements().at(i)->GetTokenType() == TokenType::STRING &&
                !std::count(domain.begin(), domain.end(), fact.GetElements().at(i)->GetDescription())) {
            domain.push_back(fact.GetElements().at(i)->GetDescription());
        }
    }
    std::sort(domain.begin(), domain.end());
}
std::string DatalogProgram::toString() {
    std::string datalogStr = "";
    datalogStr += "Schemes(" + std::to_string(schemes.size()) + "):\n";
    for (long unsigned int i = 0; i < schemes.size(); i++) {
        datalogStr += "  " + schemes.at(i).toString() + "\n";
    }
    datalogStr += "Facts(" + std::to_string(facts.size()) + "):\n";
    for (long unsigned int i = 0; i < facts.size(); i++) {
        datalogStr += "  " + facts.at(i).toString() + "\n";
    }
    datalogStr += "Rules(" + std::to_string(rules.size()) + "):\n";
    for (long unsigned int i = 0; i < rules.size(); i++) {
        datalogStr += "  " + rules.at(i).toString() + "\n";
    }
    datalogStr += "Queries(" + std::to_string(queries.size()) + "):\n";
    for (long unsigned int i = 0; i < queries.size(); i++) {
        datalogStr += "  " + queries.at(i).toString() + "\n";
    }
    datalogStr += "Domain(" + std::to_string(domain.size()) + "):\n";
    for (long unsigned int i = 0; i < domain.size(); i++) {
        datalogStr += "  " + domain.at(i) + "\n";
    }
    return datalogStr;
}