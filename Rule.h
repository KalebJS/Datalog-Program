//
// Created by Kaleb Smith on 9/28/21.
//

#ifndef RULE_H
#define RULE_H

#include <string>
#include <vector>
#include "Token.h"
#include "Predicate.h"

class Rule {
private:
    Predicate headPredicate;
    std::vector<Predicate> predicates;
public:
    Rule();

    ~Rule();

    std::string toString();

    void AddPredicate(Predicate predicate);

    void SetHeadPredicate(Predicate predicate);

    Predicate GetHeadPredicate();

    std::vector<Predicate> GetPredicates();
};

#endif //RULE_H
