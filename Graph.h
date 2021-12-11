//
// Created by Kaleb Smith on 12/9/21.
//

#ifndef DATALOG_GRAPH_H
#define DATALOG_GRAPH_H


#include <stack>
#include "DatalogProgram.h"
#include "Node.h"
#include "StronglyConnectedComponent.h"
#include <algorithm>

class Graph {
private:
    DatalogProgram *datalogProgram;
    std::vector<Rule> rules;
    std::list<Node *> nodes;
    std::stack<unsigned> postOrder;
    std::deque<Node *> nodesInOrder;

    void BreadthFirstSearch(Node *node);

    explicit Graph(Graph *graph);

public:
    explicit Graph(DatalogProgram *datalog);

    ~Graph();

    void ConstructGraph();

    std::stack<unsigned> BreadthFirstSearch();

    Graph Reverse();

    Node *GetNodeByID(unsigned int id);

    bool HasUnvisitedNodes();

    void PrintGraph();

    void PrintPostOrder();

    std::vector<StronglyConnectedComponent> BreadthFirstSearchForest(std::stack<unsigned> postOrderStack);

    void BreadthFirstSearchTree(StronglyConnectedComponent &scc, Node *node);

    bool HasNode(Node *node);

    void RemoveNodeFromOrder(Node *node);

    static void PrintSCCs(const std::vector<StronglyConnectedComponent>& sccs);
};


#endif //DATALOG_GRAPH_H
