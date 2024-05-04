#include "Edge.h"

Edge::Edge(const int &s, const int &d, double &w) {
    this->origin = s;
    this->dest = d;
    this->weight = w;
    this->direction = direction;
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

bool Edge::getDirection() const {
    return direction;
}
