//
// Created by Kaleb Smith on 12/9/21.
//

#include <sstream>
#include "StronglyConnectedComponent.h"
#include "Node.h"
#include <algorithm>


std::vector<Rule> StronglyConnectedComponent::GetRules() {
    return rules;
}

void StronglyConnectedComponent::AddComponent(Node *node) {
    rules.push_back(node->GetRule());
    nodeIDs.push_back(node->GetNodeID());
    ruleMap.insert(std::pair<unsigned, Rule>(node->GetNodeID(), node->GetRule()));

    std::sort(nodeIDs.begin(), nodeIDs.end());

    if (isTrivial && (nodeIDs.size() > 1 || node->IsSelfDependent())) {
        isTrivial = false;
    }
}

std::map<unsigned, Rule> StronglyConnectedComponent::GetRuleMap() {
    return ruleMap;
}

bool StronglyConnectedComponent::IsTrivial() const {
    return isTrivial;
}

std::string StronglyConnectedComponent::ToString() {
    std::stringstream ss;
    for (auto nodeID : nodeIDs) {
        ss << 'R' << nodeID;
        if (nodeID != nodeIDs.back()) {
            ss << ",";
        }
    }
    return ss.str();
}