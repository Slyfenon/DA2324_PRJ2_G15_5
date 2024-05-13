
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
    std::vector<int> backtracking(long &duration, double &cost);
    void triangularInequality();
    void preOrderWalk(std::vector<Edge*> MST, Vertex *v, std::vector<Vertex*> &preOrder);
    std::vector<Edge *> primMST();
    void loadExtraGraph(int option);
    void loadRealGraph(int option);

    void triangularInequality(Graph *graph);
    void realWorldHeuristic(int source);

    void resetGraph();

    Edge *findShortestEdge(Vertex *vertex, Vertex *src, bool final);
};
#endif //DA_PROJ2_MANAGER_H
