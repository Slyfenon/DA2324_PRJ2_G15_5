#include <iostream>
#include <chrono>
#include "Parser.h"
#include "Manager.h"
#include "Interface.h"


int main() {
    Interface interface;
    interface.startMenu();
    /*Parser parser = Parser();
    Manager manager = Manager();

    parser.readToyGraph("stadiums.csv", manager.getGraph());
    //std::cout << "------------------------------------------------------------" << std::endl;
    //parser.readToyGraph("stadiums.csv");
    //std::cout << "------------------------------------------------------------" << std::endl;
    //parser.readToyGraph("tourism.csv", graph);

    for(auto v : manager.getGraph()->getVertexSet()){
        v->setVisited(false);
    }

    std::vector<int> path;
    path.push_back(0);
    std::vector<int> bestPath;
    manager.getGraph()->findVertex(0)->setVisited(true);
    double minCost = std::numeric_limits<double>::max();

    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
    manager.tsp_backtracking(path, bestPath, minCost, 0.0);
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    for(auto v : bestPath){
        std::cout << v << " ";
    }
    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;



    return 0;*/
}