#include <iostream>
#include "Parser.h"


int main() {
    Parser parser;
    Graph* graph = new Graph();
    parser.readToyGraph("shipping.csv", graph);
    std::cout << "------------------------------------------------------------" << std::endl;
    //parser.readToyGraph("stadiums.csv");
    //std::cout << "------------------------------------------------------------" << std::endl;
    //parser.readToyGraph("tourism.csv", graph);
    return 0;
}