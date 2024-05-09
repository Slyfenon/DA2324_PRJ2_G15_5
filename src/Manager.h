
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
    std::vector<int>& backtracking();
    //void primMST();
    void loadExtraGraph(int option);
    void loadRealGraph(int option);
};
#endif //DA_PROJ2_MANAGER_H
