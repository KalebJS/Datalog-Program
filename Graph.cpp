//
// Created by Kaleb Smith on 12/9/21.
//

#include "Graph.h"

Graph::Graph(DatalogProgram *datalog) {
    datalogProgram = datalog;
    for (const auto &rule: datalog->getRules()) {
        rules.push_back(rule);
    }
}

void Graph::ConstructGraph() {
    unsigned idx = 0;
    for (const auto &rule: rules) {
        Node *node = new Node(rule, idx);
        nodes.push_back(node);
        idx++;
    }
    for (auto node_i: nodes) {
        for (auto node_j: nodes) {
            if (node_i->HasPredicateID(node_j)) {
                node_i->AddEdge(node_j);
            }
        }
    }
}

void Graph::BreadthFirstSearch(Node *node) {
    node->MarkAsVisited();
    for (auto edge: node->GetEdges()) {
        if (!edge->GetVisited()) {
            BreadthFirstSearch(edge);
        }
    }
    postOrder.push(node->GetNodeID());
}

std::stack<unsigned> Graph::BreadthFirstSearch() {
    Node *firstNode = nodes[0];
    BreadthFirstSearch(firstNode);
    return postOrder;
}

Graph Graph::Reverse() {
    Graph reversedGraph = Graph(this);
    std::vector<Node *> reversedNodes;
    for (auto node: nodes) {
        reversedNodes.push_back(node);
    }
    for (auto &node: nodes) {
        for (auto edge: node->GetEdges()) {
            Node *reversedNode = reversedGraph.GetNodeByID(edge->GetNodeID());
            Node *reversedEdge = reversedGraph.GetNodeByID(node->GetNodeID());
            reversedNode->AddEdge(reversedEdge);
        }
    }

    return reversedGraph;
}

Node *Graph::GetNodeByID(unsigned id) {
    for (auto node: nodes) {
        if (node->GetNodeID() == id) {
            return node;
        }
    }
    throw std::exception();
}

Graph::Graph(Graph *graph) {
    datalogProgram = graph->datalogProgram;
    for (const auto &rule: graph->rules) {
        rules.push_back(rule);
    }
    for (const auto &node: graph->nodes) {
        Node *edgelessNode = new Node(node->GetRule(), node->GetNodeID());
        nodes.push_back(edgelessNode);
    }
}

bool Graph::HasUnvisitedNodes() {
    for (auto node: nodes) {
        if (!node->GetVisited()) {
            return true;
        }
    }
    return false;
}

Graph::~Graph() {
    for (auto node: nodes) {
        delete node;
    }
}

void Graph::PrintGraph() {
    for (auto node: nodes) {
        std::cout << node->ToString() << std::endl;
    }
}

void Graph::PrintPostOrder() {
    std::cout << std::endl << "Breadth first search:" << std::endl;
    while (!postOrder.empty()) {
        unsigned node = postOrder.top();
        postOrder.pop();
        std::cout << node << " ";
    }
}

std::vector<StronglyConnectedComponent> Graph::BreadthFirstSearchForest(const std::stack<unsigned> &postOrderStack) {
//    for (auto  : postOrderStack) {

    std::vector<StronglyConnectedComponent> sccs;

    return sccs;
}