#ifndef DA_PROJ2_PARSER_H
#define DA_PROJ2_PARSER_H


#include <string>
#include "Graph.h"

class Parser {

private:


public:
    void readToyGraph(const std::string& fileName, Graph* graph);
    void readExtraGraph(Graph *graph, int option);

    void readRealGraph(Graph *graph, std::string &graphNumber);

    void readRealGraph(Graph *graph, const std::string &graphNumber);
};


#endif //DA_PROJ2_PARSER_H
