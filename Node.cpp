//
// Created by Kaleb Smith on 12/9/21.
//

#include <sstream>
#include "Node.h"

Node::Node(const Rule& rule, unsigned int id) {
    this->rule = rule;
    this->id = id;
}

bool Node::AddEdge(Node *node) {
    for (auto predicate : rule.GetPredicates()) {
        if (predicate.GetId() == node->GetRuleID()) {
            edges.push_back(node);
            return true;
        }
    }
    return false;
}

unsigned Node::GetNodeID() const {
    return id;
}

std::string Node::GetRuleID() {
    return rule.GetHeadPredicate().GetId();
}

std::string Node::ToString() const {
    std::stringstream ss;
    ss << "R" << id << ":";
    for (auto edge : edges) {
        ss << "R" << edge->GetNodeID();
        if (edge != edges.back()) {
            ss << ",";
        }
    }
    return ss.str();
}