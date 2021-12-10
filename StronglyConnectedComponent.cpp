//
// Created by Kaleb Smith on 12/9/21.
//

#include <sstream>
#include "StronglyConnectedComponent.h"
#include "Node.h"


std::vector<Rule> StronglyConnectedComponent::GetRules() {
    return rules;
}

void StronglyConnectedComponent::AddComponent(Node *node) {
    rules.push_back(node->GetRule());
    nodes.push_back(node);
    ruleMap.insert(std::pair<unsigned, Rule>(node->GetNodeID(), node->GetRule()));

    if (isTrivial && !node->GetEdges().empty()) {
        isTrivial = false;
    }

}

std::string StronglyConnectedComponent::ToString() {
    std::stringstream ss;
    for (auto node: nodes) {
        ss << "R" << node->GetNodeID() << " -> ";
    }

    return ss.str();
}

std::map<unsigned, Rule> StronglyConnectedComponent::GetRuleMap() {
    return ruleMap;
}

bool StronglyConnectedComponent::IsTrivial() {
    return isTrivial;
}