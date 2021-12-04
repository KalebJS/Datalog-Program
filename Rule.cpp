//
// Created by Kaleb Smith on 9/28/21.
//

#include "Rule.h"

Rule::Rule() {
}

Rule::~Rule() {
}

std::string Rule::toString() {
    std::string ruleStr = headPredicate.toString() + " :- " + predicates.at(0).toString();
    for (long unsigned int i = 1; i < predicates.size(); i++) {
        ruleStr += "," + predicates.at(i).toString();
    }
    ruleStr += ".";
    return ruleStr;
}

void Rule::AddPredicate(Predicate predicate) {
    predicates.push_back(predicate);
}

void Rule::SetHeadPredicate(Predicate predicate) {
    headPredicate = predicate;
}

Predicate Rule::GetHeadPredicate() {
    return headPredicate;
}

std::vector<Predicate> Rule::GetPredicates() {
    return predicates;
}
