#include <chrono>
#include <iostream>
#include <stack>
#include <queue>
#include <climits>
#include <set>
#include <cmath>
#include <set>
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
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
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

std::vector<Edge*> Manager::primMST(int source) {
    std::vector<Edge*> MST;
   for(auto v :graph->getVertexSet()){
       v.second->setDistance(std::numeric_limits<double>::max());
       v.second->setPath(nullptr);
       v.second->setVisited(false);
   }

   Vertex* root = graph->getVertexSet().find(source)->second;
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

    MSTTree = primMST(0);
    for(auto v : graph->getVertexSet()){
        v.second->setVisited(false);
    }

    Vertex* root = graph->getVertexSet().find(0)->second;
    preOrderWalk(MSTTree, root, preOrder);

    preOrder.push_back(root);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();


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

double Manager::convertBacktrack(std::vector<int> &path) {
    std::unordered_set<int> visited;
    double result = 0, prev;
    auto it = path.begin();
    bool backtracking = false;

    while(it != path.end()) {
        int node = *it;
        if (visited.find(node) == visited.end()) {
            if (!backtracking) {
                backtracking = true;
            }
            visited.insert(node);
            prev = node;
            it++;
        }
        else {
            if (backtracking) {
                for (Edge* edge : graph->findVertex(prev)->getAdj()) {
                    if (edge->getDest() == node) result += edge->getWeight();
                }
            }
            prev = node;
            it = path.erase(it);
        }
    }

    return result;
}

// Nearest neighbor heuristic
std::vector<int> Manager::realWorldHeuristic(int source, long &duration, double &cost, double &backtrack) {
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
        result.push_back(current->getId());
        if (!current->isVisited()) {
            current->setVisited(true);
            visited++;
        }
        Edge* shortest = findShortestEdge(current, src, visited == cities);
        if (!shortest) {
            result.clear();
            std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
            cost = 0;
            break;
        }
        cost += shortest->getWeight();
        shortest->setVisited(true);
        shortest->getReverse()->setVisited(true);
        current = graph->findVertex(shortest->getDest());
        current->setPath(shortest);
    } while (current != src);

    backtrack = convertBacktrack(result);

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();

    return result;
}

Vertex* Manager::findFarthestVertex(Vertex* start) {
    int res;
    double max = 0;
    for (auto e : start->getAdj()) {
        if (e->getWeight() > max && !graph->findVertex(e->getDest())->isVisited()) {
            max = e->getWeight();
            res = e->getDest();
        }
    }
    if (max == 0) {
        for (auto v : graph->getVertexSet()) {
            if (!v.second->isVisited()) {
                double d = haversineDistance(start, v.second);
                if (d > max) {
                    max = d;
                    res = v.second->getId();
                }
            }
        }
    }
    return graph->findVertex(res);
}

Edge* Manager::findEdge(Vertex* start, Vertex* end) {
    for (auto e : start->getAdj()) {
        if (e->getDest() == end->getId()) {
            return e;
        }
    }
    return graph->addEdge(start->getId(), end->getId(), haversineDistance(start, end));
}

std::vector<int> Manager::otherHeuristic(int source, long &duration, double &cost) {
    std::vector<int> res = {};
    for (auto vertex : graph->getVertexSet()) {
        vertex.second->setVisited(false);
    }

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    Vertex* src = graph->findVertex(source);
    src->setVisited(true);

    Vertex* w = findFarthestVertex(src);
    src->setPath(findEdge(src, w));
    w->setPath(findEdge(w, src));

    w->setVisited(true);

    int cnt = 2;
    while (cnt != graph->getVertexSet().size()){
        cnt++;
        w = findFarthestVertex(w);

        int min = INT_MAX;
        Vertex* prec = nullptr;
        Vertex* current = src;
        do {
            auto e1 = findEdge(current, w);
            auto e2 = findEdge(w, graph->findVertex(current->getPath()->getDest()));

            double cena = e1->getWeight() + e2->getWeight() - current->getPath()->getWeight();
            if (cena < min) {
                min = cena;
                prec = current;
            }
            current = graph->findVertex(current->getPath()->getDest());
            if (min < current->getPath()->getWeight() * 0.15) break;
        } while (current->getId() != source);

        Edge* oldTour = prec->getPath();
        prec->setPath(findEdge(prec, w));
        w->setPath(findEdge(w, graph->findVertex(oldTour->getDest())));

        w->setVisited(true);
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    Vertex* current = src;
    cost = 0;
    do {
        res.push_back(current->getId());
        cost += current->getPath()->getWeight();
        current = graph->findVertex(current->getPath()->getDest());
    } while (current->getId() != source);

    duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();
    return res;
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


void Manager::findEulerianCircuit(std::vector<int>& eulerianCircuit, Graph *eulerianGraph, int source) {
    std::unordered_map<int, Vertex*> vertexSet = eulerianGraph->getVertexSet();
    std::vector<int> currCircuit;
    currCircuit.push_back(source);

    while (eulerianCircuit.size() != eulerianGraph->getNumberOfEdges() + 1) {
        int currVertex = currCircuit.back();
        bool found = false;

        for (auto edge : vertexSet[currVertex]->getAdj()) {
            if (!edge->getVisited()) {
                edge->setVisited(true);
                found = true;

                int next = edge->getOrig() == currVertex ? edge->getDest() : edge->getOrig();
                currCircuit.push_back(next);
                break;
            }
        }


        if(!found) {
            if (eulerianCircuit.empty()) {
                eulerianCircuit = currCircuit;
            } else {
                auto it = std::find(eulerianCircuit.begin(), eulerianCircuit.end(), *currCircuit.begin());
                eulerianCircuit.insert(it + 1, currCircuit.begin() + 1, currCircuit.end());
            }

            for (auto vertex: eulerianCircuit) {
                if (std::any_of(vertexSet[vertex]->getAdj().begin(), vertexSet[vertex]->getAdj().end(),[](Edge *edge) {
                    return !edge->getVisited(); })) {
                    currCircuit = {vertex};
                    break;
                }
            }
        }
    }
}

std::vector<int> Manager::shortenToHamiltonianCircuit(const std::vector<int>& eulerianCircuit) {
    std::vector<int> hamiltonianCircuit;
    std::unordered_set<int> visited;

    for (int vertex : eulerianCircuit) {
        if (visited.find(vertex) == visited.end()) {
            hamiltonianCircuit.push_back(vertex);
            visited.insert(vertex);
        }
    }

    if (hamiltonianCircuit.front() != hamiltonianCircuit.back()) {
        hamiltonianCircuit.push_back(hamiltonianCircuit.front());
    }

    return hamiltonianCircuit;
}

void Manager::createEulerianGraph(Graph &eulerianGraph, std::vector<Edge *> &MST, std::vector<Edge *> &perfectEdges) {

    for (auto v: graph->getVertexSet()) {
        eulerianGraph.addVertex(v.first);
    }

    for (auto edge: MST) {
        eulerianGraph.addEdge(edge->getOrig(), edge->getDest(), edge->getWeight());
    }

    for (auto edge: perfectEdges) {
        eulerianGraph.addEdge(edge->getOrig(), edge->getDest(), edge->getWeight());
    }

}

auto compareEdges = [](Edge *a, Edge* b) {return a != b && a->getWeight() >= b->getWeight();};

std::vector<int> Manager::christofidesTSP(long &duration, double &cost, int source) {
        std::vector<int> result;
         std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    // Step 1: Compute Minimum Spanning Tree
        std::vector<Edge *> MST = primMST(source);

        // Step 2: Identify Odd-Degree Vertices
        std::vector<Vertex *> oddDegreeVertices;
        for (const auto &vertex: graph->getVertexSet()) {
            if ((vertex.second->getAdj().size()) % 2 != 1) {
                oddDegreeVertices.push_back(vertex.second);
            }
        }

        // Step 3: Find Minimum Weight Perfect Matching
        std::priority_queue<Edge *, std::vector<Edge *>, decltype(compareEdges)> minWeightEdgeHeap(compareEdges);
        for (auto vertex: oddDegreeVertices) {
            for (auto edge: vertex->getAdj()) {
                int next = edge->getOrig() == vertex->getId() ? edge->getDest() : edge->getOrig();
                if (!edge->getVisited() &&
                    std::find(oddDegreeVertices.begin(), oddDegreeVertices.end(), graph->findVertex(next)) !=
                    oddDegreeVertices.end()) {
                    minWeightEdgeHeap.push(edge);
                    edge->setVisited(true);
                }
            }
        }

        // Step 4: Find Perfect Edges
        std::vector<Edge *> perfectEdges;
        while (perfectEdges.size() != oddDegreeVertices.size() / 2 && !minWeightEdgeHeap.empty()) {
            Edge *edge = minWeightEdgeHeap.top();
            minWeightEdgeHeap.pop();
            if (!graph->findVertex(edge->getOrig())->isVisited() && !graph->findVertex(edge->getDest())->isVisited()) {
                perfectEdges.push_back(edge);
                graph->findVertex(edge->getOrig())->setVisited(true);
                graph->findVertex(edge->getDest())->setVisited(true);
            }
        }

        // Step 5: Create euleriangraph
        Graph eulerianGraph;
        createEulerianGraph(eulerianGraph, MST, perfectEdges);


        // Step 6: Find Eulerian Circuit
        std::vector<int> eulerianCircuit;
        findEulerianCircuit(eulerianCircuit, &eulerianGraph, source);

        // Step 7: Shorten Circuit to Hamiltonian Circuit
        result = shortenToHamiltonianCircuit(eulerianCircuit);

        std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
        duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count();

        // Step 8: Calculate cost
        cost = 0;
        for (size_t i = 0; i < result.size() - 1; i++) {
            Vertex *v1 = graph->findVertex(result[i]);
            Vertex *v2 = graph->findVertex(result[i + 1]);
            if (checkConnected(v1, v2)) {
                for (Edge *edge: v1->getAdj()) {
                    if (edge->getDest() == v2->getId()) {
                        cost += edge->getWeight();
                        break;
                    }
                }
            }
        }
        return result;
}
