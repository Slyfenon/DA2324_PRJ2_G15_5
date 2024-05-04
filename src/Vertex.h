#ifndef DA_PROJ1_VERTEX_H
#define DA_PROJ1_VERTEX_H
#include <vector>
#include <string>
#include "Edge.h"
#include "Coordinate.h"

class Vertex {
    private:
        Coordinate *coord;
        int id;
        std::vector<Edge*> adj;
        bool visited = false;
        bool processing = false;
        Edge *path = nullptr;
        std::vector<Edge *> incoming;
        friend class Graph;

    public:

        Vertex(const int& id);


        virtual int getId() const;


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

        void setCoord(Coordinate *coord);
        Coordinate *getCoord() const;

        /**
         * Getter for a vector of Edges that correspond to the Edges leaving the vertex.
         * @return Vector containing Edges that have the source vertex equal to the caller.
         */
        const std::vector<Edge*> &getAdj() const;
        friend class Graph;
};

#endif //DA_PROJ1_VERTEX_H
