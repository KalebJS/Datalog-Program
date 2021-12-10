//
// Created by Kaleb Smith on 12/9/21.
//

#ifndef DATALOG_STRONGLYCONNECTEDCOMPONENT_H
#define DATALOG_STRONGLYCONNECTEDCOMPONENT_H


#include <vector>
#include <map>
#include "Rule.h"
#include "Node.h"

class StronglyConnectedComponent {
private:
    std::vector<Rule> rules;
    std::vector<unsigned> nodeIDs;
    std::map<unsigned, Rule> ruleMap;
    bool isTrivial = true;
public:
    StronglyConnectedComponent() = default;

    std::vector<Rule> GetRules();

    void AddComponent(Node *node);

    std::string ToString();

    std::map<unsigned int, Rule> GetRuleMap();

    bool IsTrivial() const;
};


#endif //DATALOG_STRONGLYCONNECTEDCOMPONENT_H
