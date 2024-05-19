
#ifndef DA_PROJ2_MANAGER_H
#define DA_PROJ2_MANAGER_H


#include "Graph.h"
#include "Parser.h"

class Manager {
private:
    Graph *graph = new Graph();
    Parser *parser;

public:
    /**
     * @brief Invokes the parser for a specific graph in the "Toy Graph" section.
     * @complexity O(1).
     * @param option - Number of the option.
     */
    void loadToyGraph(int option);

    /**
     * @brief Employs a backtracking approach to solve the Traveling Salesman Problem.
     * @complexity O(|V|!), where |V| is the number of vertices in the graph.
     * @param path - Current path being explored.
     * @param bestPath - Best path found so far.
     * @param minCost - Minimum cost of the best path found so far.
     * @param currentCost - Cost of the current path being explored.
     */
    void tsp_backtracking(std::vector<int> &path, std::vector<int> &bestPath, double &minCost, double currentCost);

    /**
     * Wrapper function for the backtracking algorithm. Initializes the graph and organizes the cost and duration metrics of the algorithm.
     * @complexity O(|V| * |V|!), where |V| is the number of vertices in the graph.
     * @param duration - Duration of the computation.
     * @param cost - Minimal cost of the best path found.
     * @return A vector of integers, representing the vertex IDs, ordered in the way they're visited in the best path found.
     */
    std::vector<int> backtracking(long &duration, double &cost);

    /**
     * @brief Performs a pre-order traversal of the vertices in the Minimum Spanning Tree (MST).
     * @complexity O(?).
     * @param MST - Minimum Spanning Tree, represented as a vector of edges.
     * @param v - Current vertex being visited.
     * @param preOrder - Pre-order transversal sequence, represented as a vector of vertices.
     */
    void preOrderWalk(std::vector<Edge*> MST, Vertex *v, std::vector<Vertex*> &preOrder);

    /**
     * @brief Finds a Minimum Spanning Tree (MST) of the graph using Prim's algorithm.
     * @complexity O(|E| * log|V|), where |V| and |E| are the number or vertices and edges in the graph respectively.
     * @param source - The source vertex for the MST
     * @return A vector of edges, representing a MST of the graph.
     */
    std::vector<Edge *> primMST(int source);

    /**
     * @brief Invokes the parser for a specific graph in the "Extra Graph" section.
     * @complexity O(1).
     * @param option - Number of the option.
     */
    void loadExtraGraph(int option);

    /**
     * @brief Invokes the parser for a specific graph in the "Real World Graph" section.
     * @complexity O(1).
     * @param option - Number of the option.
     */
    void loadRealGraph(int option);

    /**
     * @brief Employs an heuristic approach to solve the Traveling Salesman Problem in a real world context.
     * @complexity O(|V| + |E| + |V| * d), where |V| and |E| are the number of vertices and edges of the graph respectively, and d the maximum degree of a vertex in the graph.
     * @param source - Source vertex.
     * @param duration - Duration of the computation.
     * @param cost - Minimal cost of the best path found.
     * @param backtrack - Distance travelled to vertices already visited
     * @return A vector of integers, representing the vertex IDs, ordered in the way they're visited in the best path found.
     */
    std::vector<int> realWorldHeuristic(int source, long &duration, double &cost, double &backtrack);

    /**
     * @brief Finds, if possible, the shortest edge adjacent to a vertex.
     * @complexity O(d), where d the maximum degree of a vertex in the graph.
     * @param vertex - Vertex for which to find the shortest adjacent edge.
     * @param src - Source vertex.
     * @param final - Boolean value. Indicates whether the edge connects back to the source vertex or not.
     * @return The shortest edge adjacent to the vertex (or nullptr if none is found).
     */
    Edge *findShortestEdge(Vertex *vertex, Vertex *src, bool final);

    /**
     * @brief Finds the farthest away, unvisited vertex from a given vertex in the graph.
     * @complexity O(d + |V|), where d is the degree of the given vertex, and |V| the number of vertices in the graph.
     * @param start - Starting vertex from which to find the farthest vertex.
     * @return The farthest unvisited vertex.
     */
    Vertex* findFarthestVertex(Vertex* start);

    /**
     * @brief Finds (or creates) an edge between two vertices.
     * @complexity O(d) where d is the degree of the starting vertex.
     * @param start - Origin vertex.
     * @param end - Destination vertex.
     * @return The edge between the two vertices (whether newly added or not).
     */
    Edge* findEdge(Vertex* start, Vertex* end);

    /**
     * @brief Employs another heuristic approach (Farthest Insertion Heuristic) to solve the Traveling Salesman Problem.
     * @complexity O(|V| + |E| + |V|²), where |V| and |E| are the number of vertices and edges on the graph respectively.
     * @param source - Source vertex.
     * @param duration - Duration of the computation.
     * @param cost - Minimal cost of the best path found.
     * @return A vector of integers, representing the vertex IDs, ordered in the way they're visited in the best path found.
     */
    std::vector<int> otherHeuristic(int source, long &duration, double &cost);

    /**
     * @brief Resets the graph to an initial, empty state.
     * @complexity O(1).
     */
    void resetGraph();

    /**
     * @brief Validates an input string as a node number option.
     * @complexity O(n) where n is the number of characters in the given string.
     * @param option - Input string to be validated as a valid option.
     * @return True if the input string is valid, false otherwise.
     */
    static bool validateNodeNumber(const std::string &option);

    /**
     * @brief Validates an input string as a vertex option.
     * @complexity O(n) where n is the number of characters in the given string.
     * @param option - Input string to be validated as a valid option.
     * @return True if the input string is valid, false otherwise.
     */
    bool validateVertex(const std::string &option);

    /**
     * @brief Employs the Triangular Inequality Heuristic approach to solve the Traveling Salesman Problem.
     * @complexity O((|V| + |E|) * log|V|), where |V| and |E| are the number of vertices and edges on the graph respectively.
     * @param duration - Duration of the computation.
     * @param cost - Minimal cost of the best path found.
     */
    void triangularInequality(long &duration, double &cost);

    /**
     * @brief Verifies if two vertices are connected.
     * @complexity O(d), where d is the degree of the origin vertex.
     * @param v1 - Origin vertex.
     * @param v2 - Destination vertex.
     * @return True if vertices are connected, false otherwise.
     */
    bool checkConnected(Vertex *v1, Vertex *v2);

    /**
     * @brief Computes the distance between two vertices using the Haversine formula.
     * @complexity O(1).
     * @param v1 - Origin vertex.
     * @param v2 - Destination vertex.
     * @return The distance between the two vertices.
     */
    double haversineDistance(Vertex *v1, Vertex *v2);

    /**
     * @brief Calculates the total cost of a given pre-order transversal.
     * @complexity O(|V| + |E|), where |V| and |E| are the number of vertices and edges on the graph respectively.
     * @param preorder - The pre-order transversal sequence, represented as a vector of vertices.
     * @return The cost of the transversal
     */
    double calculateCost(std::vector<Vertex *> &preorder);

    double convertBacktrack(std::vector<int> &path);

    std::vector<int> christofidesTSP(long &duration, double &cost, int source);

    std::vector<int> shortenToHamiltonianCircuit(const std::vector<int> &eulerianCircuit);

    void findEulerianCircuit(std::vector<int> &eulerianCircuit, Graph *eulerianGraph, int source);

    void createEulerianGraph(Graph &eulerianGraph, std::vector<Edge *> &MST, std::vector<Edge *> &perfectEdges);
};
#endif //DA_PROJ2_MANAGER_H
