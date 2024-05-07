#include "Coordinate.h"

void Coordinate::setLatitude(double& value) {
    this->latitude = value;
}

void Coordinate::setLongitude(double& value) {
    this->longitude = value;
}

double Coordinate::getLatitude() const {
    return latitude;
}

double Coordinate::getLongitude() const {
    return longitude;
}

Coordinate::Coordinate(double latitude, double longitude) {
    this->latitude = latitude;
    this->longitude = longitude;
}
