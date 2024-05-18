#include <chrono>
#include <iostream>
#include <stack>
#include <queue>
#include <climits>
#include <cmath>
#include "Manager.h"
#include "MutablePriorityQueue.h"

bool Manager::validateVertex(const std::string &option) {
    for (const char &c : option) {
        if (!isdigit(c)) return false;
    }
    return (graph->findVertex(stoi(option)));
}

bool Manager::validateNodeNumber(const std::string &option) {
    for (const char &c : option) {
        if (!isdigit(c)) return false;
    }
    return ((0 <= stoi(option) && stoi(option) <= 900) && (stoi(option) % 100 == 0
            || (stoi(option) % 25 == 0 && stoi(option) < 100)));
}

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

std::vector<int> Manager::backtracking(long &duration, double &cost) {
    std::vector<int> path;
    path.push_back(0);
    std::vector<int> bestPath;
    for(auto v : graph->getVertexSet()){
        v.second->setVisited(false);
    }
    graph->findVertex(0)->setVisited(true);
    double minCost = std::numeric_limits<double>::max();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    tsp_backtracking(path, bestPath, minCost, 0.0);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    cost = minCost;
    return bestPath;
}


void Manager::preOrderWalk(std::vector<Edge*> MST, Vertex* v, std::vector<Vertex*> &preOrder) {
    v->setVisited(true);
    preOrder.push_back(v);

    for (Edge* edge : v->getAdj()) {
        Vertex* w = graph->findVertex(edge->getDest());
        if (!w->isVisited()) {
            for (Edge* mstEdge : MST) {
                if ((mstEdge->getOrig() == v->getId() && mstEdge->getDest() == w->getId()) ||
                    (mstEdge->getOrig() == w->getId() && mstEdge->getDest() == v->getId())) {
                    preOrderWalk(MST, w, preOrder);
                    break;
                }
            }
        }
    }
}



std::vector<Edge*> Manager::primMST() {
    std::vector<Edge*> MST;
   for(auto v :graph->getVertexSet()){
       v.second->setDistance(std::numeric_limits<double>::max());
       v.second->setPath(nullptr);
       v.second->setVisited(false);
   }

   Vertex* root = graph->getVertexSet().find(0)->second;
   root->setDistance(0);

   MutablePriorityQueue<Vertex> queue;
   queue.insert(root);

    while (!queue.empty()){
        Vertex* u = queue.extractMin();
        u->setVisited(true);

        for(Edge* edge : u->getAdj()){
            Vertex* v = graph->findVertex(edge->getDest());
            if(!v->isVisited()) {
                auto oldDist = v->getDistance();
                if (edge->getWeight() < oldDist) {
                    v->setDistance(edge->getWeight());
                    v->setPath(edge);
                    if (oldDist == std::numeric_limits<double>::max()) {
                        queue.insert(v);
                    } else {
                        queue.decreaseKey(v);
                    }
                }
            }
        }
    }
    for(auto v : graph->getVertexSet()){
        if(v.second->getPath() != nullptr){
            MST.push_back(v.second->getPath());
        }
    }
    return MST;

}

void Manager::triangularInequality(long &duration, double &cost) {
    std::vector<Edge*> MSTTree;
    std::vector<Vertex*> preOrder;

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    for(auto v : graph->getVertexSet()){
        v.second->setVisited(false);
    }

    MSTTree = primMST();
    for(auto v : graph->getVertexSet()){
        v.second->setVisited(false);
    }

    Vertex* root = graph->getVertexSet().find(0)->second;
    preOrderWalk(MSTTree, root, preOrder);

    preOrder.push_back(root);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();


    cost = calculateCost(preOrder);
}

Edge* Manager::findShortestEdge(Vertex* vertex, Vertex* src, bool final) {
    Edge* non_visited = nullptr, *visited = nullptr;
    double min_non_visited = INF; double min_visited = INF;
    for (Edge* edge : vertex->getAdj()) {
        if (!edge->getVisited()) {
            if (final && edge->getDest() == src->getId()) {
                return edge;
            }
            if (graph->findVertex(edge->getDest())->isVisited()) {
                visited = min_visited < edge->getWeight() ? visited : edge;
                min_visited = min_visited < edge->getWeight() ? min_visited : edge->getWeight();
            } else {
                non_visited = min_non_visited < edge->getWeight() ? non_visited : edge;
                min_non_visited = min_non_visited < edge->getWeight() ? min_non_visited : edge->getWeight();
            }
        }
    }

    return non_visited == nullptr ? visited : non_visited;
}

// Nearest neighbor heuristic
std::vector<int> Manager::realWorldHeuristic(int source, long &duration, double &cost) {
    std::vector<int> result;
    cost = 0;
    int cities = graph->getVertexSet().size(), visited = 0;

    for (auto vertex : graph->getVertexSet()) {
        vertex.second->setVisited(false);
        for (Edge* edge : vertex.second->getAdj()) {
            edge->setVisited(false);
        }
    }


    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Vertex* src = graph->findVertex(source);
    Vertex* current = src;

    do {
        if (!current->isVisited()) {
            result.push_back(current->getId());
            current->setVisited(true);
            visited++;
        }
        Edge* shortest = findShortestEdge(current, src, visited == cities);
        shortest->setVisited(true);
        shortest->getReverse()->setVisited(true);
        current = graph->findVertex(shortest->getDest());
        current->setPath(shortest);
        cost += shortest->getWeight();
    } while (current != src);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    return result;

}

void Manager::resetGraph() {
    delete this->graph;
    graph = new Graph();
}

bool Manager::checkConnected(Vertex* v1, Vertex* v2 ){
    for(Edge* edge : v1->getAdj()){
        if(edge->getDest() == v2->getId()){
            return true;
        }
    }
    return false;
}

double Manager::calculateCost(std::vector<Vertex *> &preorder) {

    double cost = 0;
    for(int i = 0; i < preorder.size() - 1; i++){
        Vertex* v1 = preorder[i];
        Vertex* v2 = preorder[(i+1)];

        if(checkConnected(v1, v2)) {
            for (Edge *edge: v1->getAdj()) {
                if (edge->getDest() == v2->getId()) {
                    cost += edge->getWeight();
                    break;
                }
            }
        }
        else{
            cost += haversineDistance(v1, v2);
        }
    }
    return cost;
}

double convertToRadians(double degree){
    return degree * (M_PI/180);
}
double Manager::haversineDistance(Vertex* v1, Vertex* v2){
    double lat1 = v1->getCoord()->getLatitude();
    double lon1 = v1->getCoord()->getLongitude();
    double lat2 = v2->getCoord()->getLatitude();
    double lon2 = v2->getCoord()->getLongitude();

    double earthRadius = 6371e3;
    double phi1 = convertToRadians(lat1);
    double phi2 = convertToRadians(lat2);
    double deltaLat = convertToRadians(lat2 - lat1);
    double deltaLon = convertToRadians(lon2 - lon1);

    double a = sin(deltaLat / 2) * sin(deltaLat / 2) + cos(phi1) * cos(phi2) * sin(deltaLon / 2) * sin(deltaLon / 2);
    double c = 2 * atan2(sqrt(a), sqrt(1-a));

    return earthRadius * c;

}