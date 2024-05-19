#ifndef DA_PROJ2_PARSER_H
#define DA_PROJ2_PARSER_H


#include <string>
#include "Graph.h"

class Parser {

private:
public:
    /**
     * @brief Reads a toy graph from a file.
     * @param fileName Name of the file to be read.
     * @param graph Graph to store the read data.
     */
    void readToyGraph(const std::string& fileName, Graph* graph);
    /**
     * @brief Reads an extra graph from a file.
     * @param graph Graph to store the read data.
     * @param option Option to choose the file to be read.
     */
    void readExtraGraph(Graph *graph, int option);
    /**
     * @brief Reads a real graph from a file.
     * @param graph Graph to store the read data.
     * @param graphNumber Number of the graph to be read.
     */
    void readRealGraph(Graph *graph, const std::string &graphNumber);
};


#endif //DA_PROJ2_PARSER_H
