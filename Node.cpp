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
    if (edges.size() > 1) {
        auto itr = edges.begin();
        if ((*itr)->GetNodeID() > node->GetNodeID()) {
            edges.push_front(node);
            return;
        }
        for (; itr != edges.end(); itr++) {
            auto itr_copy = itr;
            itr_copy++;
            if (itr_copy == edges.end()) {
                edges.push_back(node);
                return;
            }
            if ((*itr)->GetNodeID() < node->GetNodeID() && (*itr_copy)->GetNodeID() > node->GetNodeID()) {
                edges.insert(itr, node);
                return;
            }
        }
    } else if (edges.size() == 1) {
        if (node->GetNodeID() < edges.front()->GetNodeID()) {
            edges.push_front(node);
        } else {
            edges.push_back(node);
        }
    } else {
        edges.push_back(node);
    }
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

std::list<Node *> Node::GetEdges() const {
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

bool Node::IsSelfDependent() {
    for (auto edge : edges) {
        if (edge == this) {
            return true;
        }
    }
    return false;
}