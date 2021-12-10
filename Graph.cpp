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
    for (auto node : nodes) {
        if (!node->GetVisited()) {
            BreadthFirstSearch(node);
        }
    }
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
    while (!nodes.empty()) {
        delete nodes.back();
        nodes.pop_back();
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

void Graph::BreadthFirstSearchTree(StronglyConnectedComponent &scc, Node *node) {
    node->MarkAsVisited();
    scc.AddComponent(node);
    RemoveNodeFromOrder(node);
    for (auto edge: node->GetEdges()) {
        if (!edge->GetVisited()) {
            BreadthFirstSearchTree(scc, edge);
        }
    }
}

bool Graph::HasNode(Node* node) {
    for (auto orderedNode : nodesInOrder) {
        if (orderedNode == node) {
            return true;
        }
    }
    return false;
}
void Graph::RemoveNodeFromOrder(Node* node) {
    std::remove(nodesInOrder.begin(), nodesInOrder.end(), node);
}

std::vector<StronglyConnectedComponent> Graph::BreadthFirstSearchForest(std::stack<unsigned> postOrderStack) {
    while (!postOrderStack.empty()) {
        unsigned nodeID = postOrderStack.top();
        postOrderStack.pop();
        nodesInOrder.push_back(GetNodeByID(nodeID));
    }

    std::vector<StronglyConnectedComponent> sccs;

    while (HasUnvisitedNodes()) {
        Node* startingNode = nodesInOrder.front();
        StronglyConnectedComponent scc = StronglyConnectedComponent();
        BreadthFirstSearchTree(scc, startingNode);
        sccs.push_back(scc);
    }

    return sccs;
}

void Graph::PrintSCCs(const std::vector<StronglyConnectedComponent>& sccs) {
    for (StronglyConnectedComponent scc: sccs) {
        std::cout << scc.ToString() << std::endl;
    }
}