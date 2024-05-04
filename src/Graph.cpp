#include <iostream>
#include "Graph.h"

Vertex* Graph::findVertex(const int &id) const {
    for (Vertex* vertex : vertexSet) {
        if (vertex->getId() == id) {
            return vertex;
        }
    }
    return nullptr;
}


bool Graph::addVertex(const int &id) {
    if (findVertex(id) != nullptr)
        return false;
    vertexSet.push_back(new Vertex(id));
    return true;
}

std::vector<Vertex *> Graph::getVertexSet() const {
    return vertexSet;
}

Edge* Graph::addEdge(const int &sourc, const int& dest, double w) {
    Vertex* source = findVertex(sourc);
    Vertex* destination = findVertex(dest);

    if (source == nullptr || destination == nullptr)
        return nullptr;

    auto newEdge = new Edge(sourc, dest, w);
    source->adj.push_back(newEdge);
    destination->incoming.push_back(newEdge);
    return newEdge;
}

void Graph::setVertexSet(std::vector<Vertex *> &v) {
    this->vertexSet = v;
}

void Graph::deleteEdge(const int &s, Edge *Edge) const{
    Vertex *dest = findVertex(Edge->getDest());
    auto it = dest->incoming.begin();
    while (it != dest->incoming.end()) {
        auto* temp = findVertex((*it)->getOrig());
        if (temp->getId() == s) {
            it = dest->incoming.erase(it);
        }
        else {
            it++;
        }
    }
    delete Edge;
}

bool Graph::removeEdge(const int &sourc, const int &dest) {
    bool removedEdge = false;

    Vertex* s = findVertex(sourc);
    Vertex* t = findVertex(dest);

    if(s == nullptr || t == nullptr){
        std::cout << "Invalid!";
        return removedEdge;
    }

    auto it = s->adj.begin();
    while (it != s->adj.end()) {
        Edge *p = *it;
        Vertex *tempDest = findVertex(p->getDest());
        if (tempDest->getId() == dest) {
            it = s->adj.erase(it);
            deleteEdge(sourc, p);
            removedEdge = true;
        }
        else {
            it++;
        }
    }
    return removedEdge;
}

bool Graph::removeVertex(const int &in) {
    auto it = vertexSet.begin();

    while (it != vertexSet.end() && (*it) != findVertex(in)) it++;

    if (it == vertexSet.end()) return false;

    Vertex* vertex = *it;

    while (!vertex->adj.empty()) {
        Edge* Edge = vertex->adj[0];
        removeEdge(Edge->getOrig(), Edge->getDest());
    }

    while (!vertex->incoming.empty()) {
        Edge* Edge = vertex->incoming[0];
        removeEdge(Edge->getOrig(), Edge->getDest());
    }

    vertexSet.erase(it);
    delete vertex;

    return true;
}


