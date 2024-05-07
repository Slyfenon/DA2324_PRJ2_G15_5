#ifndef DA_PROJ2_PARSER_H
#define DA_PROJ2_PARSER_H


#include <string>
#include "Graph.h"

class Parser {

private:


public:
    void readToyGraph(const std::string& fileName, Graph* graph);
    void readExtraGraph(Graph *graph, int option);
};


#endif //DA_PROJ2_PARSER_H
