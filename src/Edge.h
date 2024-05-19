
#ifndef DA_PROJ1_Edge_H
#define DA_PROJ1_Edge_H

#include <string>


class Edge {
private:
    int origin;
    int dest;
    double weight;
    bool visited;
    Edge *reverse;

public:

    /**
     * @brief Edge constructor.
     * @param s Source vertex.
     * @param d Destination vertex.
     * @param w Weight of the vertex.
     */
    Edge(const int &s, const int &d, double &w);

    /**
     * Getter for the destination of the Edge.
     * @return destination of the Edge.
     */
    int getDest() const;

    /**
     * Getter for the origin of the Edge.
     * @return origin of the Edge.
     */
    int getOrig() const;

    /**
     * Getter for the weight of the Edge.
     * @return weight of the Edge.
     */
    double getWeight() const;

    /**
     * Setter for the weight of the Edge.
     * @param weight weight to be set.
     */
    void setWeight(double weight);

    /**
     * Getter for the direction of the Edge.
     * @return 0 for bidirectional and  1 for unidirectional.
     */
    bool getVisited() const;

    /**
     * Set edge visited status.
     * @param b Status to be set.
     */
    void setVisited(bool b);

    /**
     * Getter for the reverse Edge.
     * @return reverse Edge.
     */
    Edge *getReverse() const;

    /**
     * Setter for the reverse Edge.
     * @param edge Edge to be set as reverse.
     */
    void setReverse(Edge *edge);
};


#endif //DA_PROJ1_Edge_H
