
#include <chrono>
#include <iostream>
#include <queue>
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

std::vector<int> &Manager::backtracking() {
    std::vector<int> path;
    path.push_back(0);
    std::vector<int> bestPath;
    graph->findVertex(0)->setVisited(true);
    double minCost = std::numeric_limits<double>::max();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    tsp_backtracking(path, bestPath, minCost, 0.0);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    for(auto v : bestPath){
        std::cout << v << " ";
    }
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;

    return bestPath;
}

struct PrimVertexInfo {
    int id;
    double key;
    int parent;
};

struct CompareVertexKeys {
    bool operator()(const PrimVertexInfo& v1, const PrimVertexInfo& v2) {
        return v1.key > v2.key;
    }
};


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
    auto vertexSet = graph->getVertexSet();
    unsigned long numVertices = vertexSet.size();

    std::vector<bool> inMST(numVertices, false);
    std::vector<PrimVertexInfo> primInfo(numVertices);
    std::vector<Edge*> MSTEdges(numVertices - 1);

    for (auto& entry : vertexSet) {
        int id = entry.first;
        primInfo[id].id = id;
        primInfo[id].key = std::numeric_limits<double>::max();
        primInfo[id].parent = -1;
    }

    primInfo[0].key = 0;

    std::priority_queue<PrimVertexInfo, std::vector<PrimVertexInfo>, CompareVertexKeys> pq;
    for (int i = 0; i < numVertices; ++i)
        pq.push(primInfo[i]);

    while (!pq.empty()) {
        PrimVertexInfo u = pq.top();
        pq.pop();

        inMST[u.id] = true;

        for (Edge* edge : vertexSet[u.id]->getAdj()) {
            int v = edge->getDest();
            if (!inMST[v] && edge->getWeight() < primInfo[v].key) {
                primInfo[v].parent = u.id;
                primInfo[v].key = edge->getWeight();
                pq.push(primInfo[v]);
            }
        }
    }

    int edgeIndex = 0;
    for (int i = 1; i < numVertices; ++i) {
        int parent = primInfo[i].parent;
        for (Edge* edge : vertexSet[i]->getAdj()) {
            if (edge->getDest() == parent) {
                MSTEdges[edgeIndex++] = edge;
                break;
            }
        }
    }

    return MSTEdges;

}

void Manager::triangularInequality() {
    std::vector<Edge*> MSTTree;
    std::vector<Vertex*> preOrder;
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

    int count = 0;
    for(auto v : preOrder){
        count++;
        std::cout << v->getId() << " ";
    }
    std::cout << std::endl;
    std::cout << count <<std::endl;
}

