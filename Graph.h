//
// Created by Kaleb Smith on 12/9/21.
//

#ifndef DATALOG_GRAPH_H
#define DATALOG_GRAPH_H


#include "DatalogProgram.h"
#include "Node.h"

class Graph {
private:
    DatalogProgram *datalogProgram;
    std::vector<Rule> rules;
    std::vector<Node*> nodes;
public:
    Graph(DatalogProgram *datalog);

    void ConstructGraph();
};


#endif //DATALOG_GRAPH_H
