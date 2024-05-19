#ifndef DA_PROJ1_VERTEX_H
#define DA_PROJ1_VERTEX_H
#include <vector>
#include <string>
#include "Edge.h"
#include "Coordinate.h"
#include "MutablePriorityQueue.h"

class Vertex {
    private:
        Coordinate *coord;
        int id;
        std::string label;
        std::vector<Edge*> adj;
        double distance = 0;
        bool visited = false;
        bool processing = false;
        Edge *path = nullptr;
        int queueIndex = 0; 		// required by MutablePriorityQueue
        std::vector<Edge *> incoming;
        friend class Graph;
        friend class MutablePriorityQueue<Vertex>;

    public:
        /**
         * @brief Vertex constructor.
         * @param id Id of the vertex.
         */
        Vertex(const int& id);

        /**
         * @brief Compares two vertexes by their distance.
         * @param vertex Vertex to be compared.
         * @return True if the distance of the caller is less than the distance of the vertex, false otherwise.
         */
        bool operator<(Vertex & vertex) const; // // required by MutablePriorityQueue

        /**
         * Getter for the id attribute.
         * @return
         */
        virtual int getId() const;

        /**
         * Setter for the label attribute.
         * @param label
         */
        void setLabel(const std::string &label);

        /**
         * Getter for the label attribute.
         * @return Label of the vertex.
         */
        std::string getLabel() const;

        /**
         * Setter for the distance attribute.
         * @param distance
         */
        void setDistance(double distance);

        /**
         * Getter for the distance attribute.
         * @return Distance of the vertex.
         */
        double getDistance() const;

        /**
         * Checks visited attribute.
         * @return True if vertex is visited or false otherwise.
         */
        bool isVisited() const;

        /**
         * Setter for visited attribute.
         * @param v Value to be assigned to visited attribute.
         */
        void setVisited(bool v);

        /**
         * Getter for the vertex path.
         * @return Pipe corresponding to the path of the vertex.
         */
        Edge* getPath() const;

        /**
         * Setter for the vertex path.
         * @param path Edge to be set as path of the vertex.
         */
        void setPath(Edge* path);

        /**
         * Getter for a vector of Edges that correspond to the Edges incoming to the vertex.
         * @return Vector containing Edges that have the source vertex equal to the caller.
         */
        std::vector<Edge *> getIncoming() const;

        /**
         * Setter for the Coordinate of the vertex.
         * @param coord
         */
        void setCoord(Coordinate *coord);
        /**
         * Getter for the Coordinate of the vertex.
         * @return Coordinate of the vertex.
         */
        Coordinate *getCoord() const;

        /**
         * Getter for a vector of Edges that correspond to the Edges leaving the vertex.
         * @return Vector containing Edges that have the source vertex equal to the caller.
         */
        const std::vector<Edge*> &getAdj() const;

        friend class Graph;
};

#endif //DA_PROJ1_VERTEX_H
