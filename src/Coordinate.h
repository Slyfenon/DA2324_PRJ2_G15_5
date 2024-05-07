
#ifndef DA_PROJ2_COORDINATE_H
#define DA_PROJ2_COORDINATE_H


class Coordinate {
private:
    double latitude;
    double longitude;
public:
    Coordinate(double latitude, double longitude);
    void setLatitude(double& value);
    void setLongitude(double& value);
    double getLatitude() const;
    double getLongitude() const;

};


#endif //DA_PROJ2_COORDINATE_H
