
#ifndef DA_PROJ1_Edge_H
#define DA_PROJ1_Edge_H

#include <string>


class Edge {
    private:
        int origin;
        int dest;
        double weight;
        bool direction;

    public:

        /**
         * @brief Edge constructor.
         * @param s Source vertex.
         * @param d Destination vertex.
         * @param w Weight of the vertex.
         */
        Edge(const int &s, const int &d, double &w);




        int getDest() const;


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
        bool getDirection() const;
};


#endif //DA_PROJ1_Edge_H
