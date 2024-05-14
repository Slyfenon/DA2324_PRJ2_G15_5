
#ifndef DA_PROJ2_MANAGER_H
#define DA_PROJ2_MANAGER_H


#include "Graph.h"
#include "Parser.h"

class Manager {
private:
    Graph *graph = new Graph();
    Parser *parser;

    Edge *findShortestEdge(Vertex *vertex, Vertex *src, bool final);

public:
    Graph* getGraph() const;
    void loadToyGraph(int option);
    void tsp_backtracking(std::vector<int> &path, std::vector<int> &bestPath, double &minCost, double sumCost);
    std::vector<int> backtracking(long &duration, double &cost);
    void triangularInequality();
    void preOrderWalk(std::vector<Edge*> MST, Vertex *v, std::vector<Vertex*> &preOrder);
    std::vector<Edge *> primMST();
    void loadExtraGraph(int option);
    void loadRealGraph(int option);
    std::vector<int> realWorldHeuristic(int source, long &duration, double &cost);

    void resetGraph();

    static bool validateEdgeNumber(const std::string &option);
    bool validateVertex(const std::string &option);
};
#endif //DA_PROJ2_MANAGER_H
