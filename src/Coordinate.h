
#ifndef DA_PROJ2_COORDINATE_H
#define DA_PROJ2_COORDINATE_H


class Coordinate {
private:
    double latitude;
    double longitude;
public:
    /**
     * @brief Coordinate constructor.
     * @param latitude Latitude of the coordinate.
     * @param longitude Longitude of the coordinate.
     */
    Coordinate(double latitude, double longitude);
    /**
     * @brief Setter for the latitude attribute.
     * @param value Value to be set.
     */
    void setLatitude(double& value);
    /**
     * @brief Setter for the longitude attribute.
     * @param value
     */
    void setLongitude(double& value);
    /**
     * @brief Getter for the latitude attribute.
     * @return Latitude of the coordinate.
     */
    double getLatitude() const;
    /**
     * @brief Getter for the longitude attribute.
     * @return Longitude of the coordinate.
     */
    double getLongitude() const;

};


#endif //DA_PROJ2_COORDINATE_H
