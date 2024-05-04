
#ifndef DA_PROJ2_MANAGER_H
#define DA_PROJ2_MANAGER_H


#include "Graph.h"

class Manager {
private:
    Graph *graph = new Graph();

public:
    Graph* getGraph() const;
    void tsp_backtracking(std::vector<int> &path, std::vector<int> &bestPath, double &minCost, double sumCost);

};
#endif //DA_PROJ2_MANAGER_H
