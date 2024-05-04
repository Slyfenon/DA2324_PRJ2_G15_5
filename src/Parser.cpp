#include <fstream>
#include <sstream>
#include <iostream>
#include "Parser.h"


void Parser::readToyGraph(const std::string& fileName, Graph* graph) {


    bool tourism = false;
    if(fileName == "tourism.csv")
        tourism = true;

    std::ifstream inputFile;
    std::istringstream iss;
    std::string line;

    std::string origin, dest, dist, originLabel, destLabel;

    inputFile.open("../data/toy/" + fileName);
    getline(inputFile, line);
    while(getline(inputFile, line)) {
        iss.clear();
        iss.str(line);

        getline(iss, origin, ',');
        getline(iss, dest, ',');
        if (!tourism)
            getline(iss, dist, '\r');
        else {
            getline(iss, dist, ',');
            getline(iss, originLabel, ',');
            getline(iss, destLabel, '\r');
        }

        if (!tourism) {
            graph->addVertex(stoi(origin));
            graph->addVertex(stoi(dest));
            graph->addEdge(stoi(origin), stoi(dest), stod(dist));
        } else {
            graph->addVertex(stoi(origin));
            graph->addVertex(stoi(dest));
            Vertex *v = graph->findVertex(stoi(origin));
            v->setLabel(originLabel);
            v = graph->findVertex(stoi(dest));
            v->setLabel(destLabel);
            graph->addEdge(stoi(origin), stoi(dest), stod(dist));
        }
    }
    for(auto v : graph->getVertexSet()){
        std::cout << "- " << v->getId() << v->getLabel() << std::endl;
        for(auto e : v->getAdj()){
            std::cout << e->getOrig() <<" "<<e->getDest()<< " "<< e->getWeight() << std::endl;
        }
    }

}

