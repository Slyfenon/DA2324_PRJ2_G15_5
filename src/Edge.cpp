#include "Edge.h"

Edge::Edge(const int &s, const int &d, double &w) {
    this->origin = s;
    this->dest = d;
    this->weight = w;
}


int Edge::getDest() const {
    return dest;
}

int Edge::getOrig() const {
    return origin;
}

double Edge::getWeight() const {
    return weight;
}

void Edge::setWeight(double weight) {
    this->weight = weight;
}

Edge *Edge::getReverse() const {
    return this->reverse;
}

void Edge::setReverse(Edge *edge) {
    this->reverse = edge;
}

bool Edge::getVisited() const {
    return this->visited;
}

void Edge::setVisited(bool b) {
    this->visited = b;
}
