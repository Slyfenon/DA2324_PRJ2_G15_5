#ifndef DA_PROJ2_INTERFACE_H
#define DA_PROJ2_INTERFACE_H

#include "Manager.h"
#include "Parser.h"
#include <bits/stdc++.h>

#define RESET       "\033[0m"
#define BOLD        "\033[1m"
#define FAINT       "\033[2m"

#define RED         "\033[31m"
#define GREEN       "\033[32m"
#define YELLOW      "\033[33m"
#define BLUE        "\033[34m"

class Interface {

private:
    Manager manager = Manager();

    void clear();
    void header();
    void footer();
    void inputWait();
    int readOption(unsigned int options);
    int readNodeNumber();
    int readVertex();
    bool readPath();

public:

    void startMenu();
    void mainMenu();
    void exitMenu();
    void loadToyGraphMenu();
    void loadRealGraphMenu();
    void loadExtraGraphMenu();
    void triangularHeuristicMenu();
    void otherHeuristicMenu();
    void realWorldGraphsMenu();

    void printBacktracking();
    void printRealWorldHeuristic(int option);
    void printTriangularInequality(bool compare);
    void printOtherHeuristic(bool compare);
    void printPath(std::vector<int> path);
};


#endif //DA_PROJ2_INTERFACE_H
