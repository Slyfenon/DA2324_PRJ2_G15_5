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
            graph->addEdge(stoi(dest), stoi(origin), stod(dist));
        } else {
            graph->addVertex(stoi(origin));
            graph->addVertex(stoi(dest));
            Vertex *v = graph->findVertex(stoi(origin));
            v->setLabel(originLabel);
            v = graph->findVertex(stoi(dest));
            v->setLabel(destLabel);
            graph->addEdge(stoi(origin), stoi(dest), stod(dist));
            graph->addEdge(stoi(dest), stoi(origin), stod(dist));
        }
    }

}

void Parser::readExtraGraph(Graph *graph, int option) {
    std::ifstream inputFile;
    std::istringstream iss;
    std::string line;

    std::string id, origin, dest, dist, originLabel, destLabel,
            longitude, latitude;

    inputFile.open("../data/extra/nodes.csv");
    getline(inputFile, line);
    while (getline(inputFile, line)) {
        iss.clear();
        iss.str(line);

        getline(iss, id, ',');
        getline(iss, longitude, ',');
        getline(iss, latitude, '\r');

        graph->addVertex(stoi(id));
        Vertex *v = graph->findVertex(stoi(id));
        v->setCoord(new Coordinate(stod(longitude), stod(latitude)));
    }
    inputFile.close();

    int counter = 25;
    int sum = 25;
    while (counter <= option || (counter % 100 == 0 && counter <= 1000)) {
        inputFile.open("../data/extra/edges_" + std::to_string(counter) + ".csv");
        counter += sum;
        if(counter == 100) sum = 100;

        while(getline(inputFile, line)) {
            iss.clear();
            iss.str(line);

            getline(iss, origin, ',');
            getline(iss, dest, ',');
            getline(iss, dist, '\r');

            graph->addEdge(stoi(origin), stoi(dest), stod(dist));
            graph->addEdge(stoi(dest), stoi(origin), stod(dist));
        }
        inputFile.close();
    }
}

