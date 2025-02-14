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
            Edge* a = graph->addEdge(stoi(origin), stoi(dest), stod(dist));
            Edge* b = graph->addEdge(stoi(dest), stoi(origin), stod(dist));

            a->setReverse(b); b->setReverse(a);
        } else {
            graph->addVertex(stoi(origin));
            graph->addVertex(stoi(dest));
            Vertex *v = graph->findVertex(stoi(origin));
            v->setLabel(originLabel);
            v = graph->findVertex(stoi(dest));
            v->setLabel(destLabel);
            Edge* a = graph->addEdge(stoi(origin), stoi(dest), stod(dist));
            Edge* b = graph->addEdge(stoi(dest), stoi(origin), stod(dist));

            a->setReverse(b); b->setReverse(a);
        }
    }

}

void Parser::readExtraGraph(Graph *graph, int option) {
    std::ifstream inputFile;
    std::istringstream iss;
    std::string line;

    int counter = 0;

    std::string id, origin, dest, dist, originLabel, destLabel,
            longitude, latitude;


    inputFile.open("../data/extra/nodes.csv");
    getline(inputFile, line);
    while (getline(inputFile, line)  && counter < option) {
        if(counter > option)
            break;
        iss.clear();
        iss.str(line);

        getline(iss, id, ',');
        getline(iss, longitude, ',');
        getline(iss, latitude, '\r');

        graph->addVertex(stoi(id));
        Vertex *v = graph->findVertex(stoi(id));
        v->setCoord(new Coordinate(stod(longitude), stod(latitude)));
        counter++;
    }
    inputFile.close();

    inputFile.open("../data/extra/edges_" + std::to_string(option) + ".csv");
    while(getline(inputFile, line)) {
        iss.clear();
        iss.str(line);

        getline(iss, origin, ',');
        getline(iss, dest, ',');
        getline(iss, dist, '\r');

        Edge* a = graph->addEdge(stoi(origin), stoi(dest), stod(dist));
        Edge* b = graph->addEdge(stoi(dest), stoi(origin), stod(dist));

        a->setReverse(b); b->setReverse(a);
    }
    inputFile.close();
}

void Parser::readRealGraph(Graph *graph, const std::string& graphNumber){

    std::ifstream inputFile;
    std::istringstream iss;
    std::string line;

    std::string id, origin, dest, dist,
    longitude, latitude;

    inputFile.open("../data/real/" + graphNumber + "/nodes.csv");
    getline(inputFile, line);
    while(getline(inputFile, line)) {
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

    inputFile.open("../data/real/" + graphNumber + "/edges.csv");
    getline(inputFile, line);
    while(getline(inputFile, line)) {
        iss.clear();
        iss.str(line);

        getline(iss, origin, ',');
        getline(iss, dest, ',');
        getline(iss, dist, '\r');

        Edge* a = graph->addEdge(stoi(origin), stoi(dest), stod(dist));
        Edge* b = graph->addEdge(stoi(dest), stoi(origin), stod(dist));

        a->setReverse(b); b->setReverse(a);
    }
    inputFile.close();
}
