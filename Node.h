//
// Created by Kaleb Smith on 12/9/21.
//

#ifndef DATALOG_NODE_H
#define DATALOG_NODE_H


#include <set>
#include <algorithm>
#include <list>
#include "Rule.h"

class Node {
private:
    Rule rule;
    unsigned id;
    std::list<Node *> edges;
    bool isVisited = false;
public:
    Node(const Rule &rule, unsigned id);

    void AddEdge(Node *node);

    std::string GetRuleID();

    std::string ToString() const;

    unsigned int GetNodeID() const;

    std::list<Node *> GetEdges() const;

    Rule GetRule() const;

    void MarkAsVisited();

    bool GetVisited() const;

    bool HasPredicateID(Node *node);

    bool IsSelfDependent();

    bool operator<(const Node &rhs) const;

    bool operator>(const Node &rhs) const;

    bool operator<=(const Node &rhs) const;

    bool operator>=(const Node &rhs) const;
};


#endif //DATALOG_NODE_H
