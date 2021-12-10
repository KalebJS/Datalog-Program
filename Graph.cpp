//
// Created by Kaleb Smith on 12/9/21.
//

#include "Graph.h"

Graph::Graph(DatalogProgram *datalog) {
    datalogProgram = datalog;
    for (const auto& rule : datalog->getRules()) {
        rules.push_back(rule);
    }
}

void Graph::ConstructGraph() {
    unsigned idx = 0;
    for (const auto& rule : rules) {
        Node *node = new Node(rule, idx);
        nodes.push_back(node);
        idx++;
    }
    for (auto node_i : nodes) {
        for (auto node_j : nodes) {
            node_i->AddEdge(node_j);
        }
    }

    for (auto node : nodes) {
        std::cout << node->ToString() << std::endl;
    }
}
