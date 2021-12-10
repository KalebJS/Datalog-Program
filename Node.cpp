//
// Created by Kaleb Smith on 12/9/21.
//

#include <sstream>
#include "Node.h"

Node::Node(const Rule &rule, unsigned int id) {
    this->rule = rule;
    this->id = id;
}

bool Node::HasPredicateID(Node *node) {
    for (auto predicate: rule.GetPredicates()) {
        if (predicate.GetId() == node->GetRuleID()) {
            return true;
        }
    }
    return false;
}

void Node::AddEdge(Node *node) {
    edges.push_back(node);
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
    for (auto edge: edges) {
        ss << "R" << edge->GetNodeID();
        if (edge != edges.back()) {
            ss << ",";
        }
    }
    return ss.str();
}

std::vector<Node *> Node::GetEdges() const {
    return edges;
}

Rule Node::GetRule() const {
    return rule;
}

void Node::MarkAsVisited() {
    isVisited = true;
}

bool Node::GetVisited() const {
    return isVisited;
}