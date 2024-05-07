
#include "Manager.h"

void checkAndUpdateBestPath(const std::vector<int>& path, std::vector<int>& bestPath, double& minCost, double currentCost, int firstVertex, Graph* graph) {

    for (Edge* edge : graph->findVertex(path.back())->getAdj()) {
        Vertex* first = graph->findVertex(edge->getDest());
        if (first->getId() == firstVertex) {
            double cycleCost = currentCost + edge->getWeight();
            if (cycleCost < minCost) {
                minCost = cycleCost;
                bestPath = path;
            }
            break;
        }
    }
}

void Manager::tsp_backtracking(std::vector<int> &path, std::vector<int> &bestPath, double &minCost, double currentCost) {
    int lastVertex = path.back();
    int firstVertex = path.front();

    if (path.size() == graph->getVertexSet().size()) {
        checkAndUpdateBestPath(path, bestPath, minCost, currentCost, firstVertex, graph);
        return;
    }

    for (Edge* edge : graph->findVertex(lastVertex)->getAdj()) {
        Vertex* nextVertex = graph->findVertex(edge->getDest());
        if (!nextVertex->isVisited()) {
            double nextCost = currentCost + edge->getWeight();
            path.push_back(nextVertex->getId());
            nextVertex->setVisited(true);
            tsp_backtracking(path, bestPath, minCost, nextCost);
            path.pop_back();
            nextVertex->setVisited(false);
        }
    }
}




Graph *Manager::getGraph() const {
    return graph;
}

void Manager::loadToyGraph(int option) {
    switch (option) {
        case 1:
            parser->readToyGraph("shipping.csv", graph);
            break;
        case 2:
            parser->readToyGraph("stadiums.csv", graph);
            break;
        case 3:
            parser->readToyGraph("tourism.csv", graph);
            break;
        default:
            break;

    }
}

void Manager::loadExtraGraph(int option) {
    parser->readExtraGraph(graph, option);
}

void Manager::loadRealGraph(int option) {
    switch (option) {
        case 1:
            parser->readRealGraph(graph, "graph1");
            break;
        case 2:
            parser->readRealGraph(graph, "graph2");
            break;
        case 3:
            parser->readRealGraph( graph, "graph3");
            break;
        default:
            break;

    }

}

