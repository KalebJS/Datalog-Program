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
}

std::string StronglyConnectedComponent::ToString() {
    std::stringstream ss;
    for (auto node : nodes) {
        ss << "R" << node->GetNodeID() << " -> ";
    }

    return ss.str();
}