
#ifndef DA_PROJ2_MANAGER_H
#define DA_PROJ2_MANAGER_H


#include "Graph.h"
#include "Parser.h"

class Manager {
private:
    Graph *graph = new Graph();
    Parser *parser;

public:
    Graph* getGraph() const;
    void loadToyGraph(int option);
    void tsp_backtracking(std::vector<int> &path, std::vector<int> &bestPath, double &minCost, double sumCost);

    void loadExtraGraph(int option);
};
#endif //DA_PROJ2_MANAGER_H
