//
// Created by Kaleb Smith on 12/9/21.
//

#ifndef DATALOG_STRONGLYCONNECTEDCOMPONENT_H
#define DATALOG_STRONGLYCONNECTEDCOMPONENT_H


#include <vector>
#include "Rule.h"
#include "Node.h"

class StronglyConnectedComponent {
private:
    std::vector<Rule> rules;
    std::vector<Node*> nodes;
public:
    StronglyConnectedComponent() = default;

    std::vector<Rule> GetRules();

    void AddComponent(Node *node);

    std::string ToString();
};


#endif //DATALOG_STRONGLYCONNECTEDCOMPONENT_H
