//
// Created by Kaleb Smith on 12/9/21.
//

#ifndef DATALOG_GRAPH_H
#define DATALOG_GRAPH_H


#include <stack>
#include "DatalogProgram.h"
#include "Node.h"

class Graph {
private:
    DatalogProgram *datalogProgram;
    std::vector<Rule> rules;
    std::vector<Node *> nodes;
    std::stack<Node *> postOrder;

    void BreadthFirstSearch(Node *node);

    explicit Graph(Graph *graph);

public:
    explicit Graph(DatalogProgram *datalog);

    ~Graph();

    void ConstructGraph();

    std::stack<Node *> BreadthFirstSearch();

    Graph Reverse();

    Node *GetNodeByID(unsigned int id);

    bool HasUnvisitedNodes();

    void PrintGraph();

    void PrintPostOrder();
};


#endif //DATALOG_GRAPH_H
