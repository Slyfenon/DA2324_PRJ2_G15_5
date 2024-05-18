
#include "Vertex.h"

Vertex::Vertex(const int& id) : id(id) {}

int Vertex::getId() const {
    return id;
}


const std::vector<Edge *> &Vertex::getAdj() const {
    return this->adj;
}

Edge *Vertex::getPath() const {
    return path;
}

void Vertex::setPath(Edge *path) {
    this->path = path;
}

std::vector<Edge *> Vertex::getIncoming() const {
    return incoming;
}

void Vertex::setVisited(bool v) {
    this->visited = v;
}

bool Vertex::isVisited() const {
    return visited;
}

void Vertex::setCoord(Coordinate *coord) {
    this->coord = coord;
}

Coordinate *Vertex::getCoord() const {
    return coord;
}

void Vertex::setLabel(const std::string &label) {
    this->label = label;
}

std::string Vertex::getLabel() const {
    return label;
}

void Vertex::setDistance(double distance) {
    this->distance = distance;
}

double Vertex::getDistance() const {
    return distance;
}

bool Vertex::operator<(Vertex &vertex) const {
    return this->distance < vertex.distance;
}
