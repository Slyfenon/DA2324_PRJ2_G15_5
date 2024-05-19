#ifndef DA_PROJ1_GRAPH_H
#define DA_PROJ1_GRAPH_H

#include "Vertex.h"
#include <vector>
#include <limits>
#include <algorithm>
#include <string>
#include <unordered_set>
#include <unordered_map>

#define INF std::numeric_limits<double>::max();

class Graph {

protected:
    std::unordered_map<int,Vertex*> vertexSet;

public:
    /**
     * Searches for the vertex code in vertex set.
     * @param code Code of the vertex.
     * @return Corresponding Vertex if it finds the code in the vertex set, nullptr otherwise.
     * Complexity: O(v), where v in the number of vertexes in vertex set.
     */
    Vertex* findVertex(const int &id) const;

    /**
     * Getter for the number of vertexes in the vertex set.
     * @return
     */
    int getNumberOfEdges() const;


    /**
     * Removes the vertex from the vertex set, his adjacent Edges and his incoming Edges.
     * @param in Code of the vertex to be removed.
     * @return True if successfully removed, False otherwise.
     */
    bool removeVertex(const int &in);

    /**
     * Adds a Edge connecting tow vertexes, checks if the vertexes exists first.
     * @param sourc Source vertex.
     * @param dest Destination vertex.
     * @param w Weight of the Edge.
     * @param direction Direction of the edge
     * @return The new Edge created or nullptr if one of the vertexes not found.
     */
    Edge* addEdge(const int &sourc, const int &dest, double w);

    /**
     * Removes an Edge connecting two vertexes.
     * @param sourc Source vertex.
     * @param dest Destination vertex.
     * @return True if successfully remover, False otherwise.
     */
    bool removeEdge(const int &sourc, const int &dest);

    /**
     * Getter for the VertexSet.
     * @return Vector of Vertexes corresponding to the VertexSet.
     */
    std::unordered_map<int, Vertex *> getVertexSet() const;

    /**
     * Setter for the VertexSet.
     * @param v Vector of Vertexes to be set as the new VertexSet.
     */
    void setVertexSet(std::unordered_map<int, Vertex*> &v);

    /**
     * Adds a new Vertex to the Vertex Set verifying if it already exists.
     * @param code Code of the Vertex to be removed.
     * @return True if it successfully removes, False otherwise.
     */
    bool addVertex(const int& id);

    /**
     * Removes all incoming Edges.
     * @param s Vertex code.
     * @param Edge
     */
    void deleteEdge(const int &s, Edge *Edge) const;
};

#endif //DA_PROJ1_GRAPH_H
