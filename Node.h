//
// Created by Kaleb Smith on 12/9/21.
//

#ifndef DATALOG_NODE_H
#define DATALOG_NODE_H


#include <set>
#include "Rule.h"

class Node {
private:
    Rule rule;
    unsigned id;
    std::vector<Node*> edges;
public:
    Node(const Rule& rule, unsigned id);


    bool AddEdge(Node *node);

    std::string GetRuleID();

    std::string ToString() const;

    unsigned int GetNodeID() const;
};


#endif //DATALOG_NODE_H
