#include "Interface.h"

using namespace std;

void Interface::clear() {
    system("clear");
}

void Interface::header() {
    clear();
    std::cout << BOLD << " _________________________________________________________________________________________\n"
              << "/-----/-----/-----/-----/-----/-----/-----/-----\\-----\\-----\\-----\\-----\\-----\\-----\\-----\\\n"
              << "" << RESET << "|------------------------------- " << BOLD << BLUE << "TSP Calculator (Group 5)" << RESET <<" --------------------------------|" << BOLD << "\n\n" << RESET;
}

void Interface::footer() {

    std::cout << BOLD << "\n\n" << "|------------------------------  " << BOLD << BLUE << "TSP Calculator (Group 5)" << RESET << " --------------------------------|\n";
}

void Interface::inputWait() {
    cin.clear();
    cout << "\n\n\t\t\t       " << FAINT << "< Press " << RESET << BOLD << "ENTER" << RESET << FAINT << " to Continue >" << RESET;
    cin.ignore();
}

int Interface::readOption(unsigned int options) {
    string option;
    do {
        cout << BOLD << BLUE << "\n\tOption: " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (!(option.size() == 1 && "0" <= option && option <= to_string(options)));

    return stoi(option);
}

int Interface::readNodeNumber() {
    string option;
    do {
        cout << BOLD << BLUE << "\n\tNode Number: " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (!Manager::validateNodeNumber(option));

    return stoi(option);
}

int Interface::readVertex() {
    string option;
    do {
        cout << BOLD << BLUE << "\n\tVertex: " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (!manager.validateVertex(option) && option != "-1");

    return stoi(option);
}

bool Interface::readPath() {
    string option;
    do {
        cout << "\n\tWould you like to print" << BLUE << " the path" << RESET << "? [yes/no]: ";
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (option != "yes" && option != "no");

    return option == "yes";
}

void Interface::startMenu() {
    clear();
    header();

    cout << "\tWhich " << BOLD << BLUE << "type of graphs" << RESET " would you like to load?\n" << endl
    << BOLD << BLUE << "\t[1]" << RESET << " - Toy Graph" << endl
    << BOLD << BLUE << "\t[2]" << RESET << " - Extra Graph" << endl
    << BOLD << BLUE << "\t[3]" << RESET << " - Real World Graph" << endl
    << BOLD << RED << "\t[0]" << RESET << " - Exit" << endl;

    footer();

    int option = readOption(3);

    switch(option) {
        case 1:
            loadToyGraphMenu();
            break;
        case 2:
            loadExtraGraphMenu();
            break;
        case 3:
            loadRealGraphMenu();
            break;
        case 0:
            exitMenu();
            break;
        default:
            startMenu();
            break;
    }
}

void Interface::mainMenu() {
    clear();
    header();

    cout << "\tWhich " << BOLD << BLUE << "TSP Algorithm" << RESET " would you like to run?\n" << endl
         << BOLD << BLUE << "\t[1]" << RESET << " - Backtracking" << endl
         << BOLD << BLUE << "\t[2]" << RESET << " - Triangular Approximantion Heuristic" << endl
         << BOLD << BLUE << "\t[3]" << RESET << " - ??? Heuristic" << endl
         << BOLD << BLUE << "\t[4]" << RESET << " - Arbitrary Starting Point" << endl
         << BOLD << BLUE << "\t[5]" << RESET << " - Christofides Algorithm" << endl
         << BOLD << RED << "\t[0]" << RESET << " - Back" << endl;

    footer();

    int option = readOption(5);

    double cost;
    long duration;
    switch(option) {
        case 1:
            printBacktracking();
            break;
        case 2:
            triangularHeuristicMenu();
            break;
        case 3:
            otherHeuristicMenu();
            break;
        case 4:
            realWorldGraphsMenu();
            break;
        case 5:
            christofidesMenu();
            break;
        case 0:
            manager.resetGraph();
            startMenu();
        default:
            mainMenu();
            break;
    }

    mainMenu();
}

void Interface::exitMenu() {
    clear();
    header();

    cout << BOLD << "\n\t\t\t   Thank you for using our TSP Calculator!" << RESET << endl;

    footer();
    exit(EXIT_SUCCESS);
}

void Interface::loadToyGraphMenu() {
    clear();
    header();

    cout << "\tWhich " << BOLD << BLUE << "toy graph" << RESET " would you like to load?\n" << endl
         << BOLD << BLUE << "\t[1]" << RESET << " - Shipping Graph" << endl
         << BOLD << BLUE << "\t[2]" << RESET << " - Stadiums Graph" << endl
         << BOLD << BLUE << "\t[3]" << RESET << " - Tourism Graph" << endl
         << BOLD << RED << "\t[0]" << RESET << " - Back" << endl;

    footer();

    int option = readOption(3);

    if (option == 0) startMenu();
    else {
        manager.loadToyGraph(option);
        mainMenu();
    };
}

void Interface::loadRealGraphMenu() {
    clear();
    header();

    cout << "\n     Enter the number" << BOLD << BLUE <<  " (1-3)" << RESET
    << " of the " << BOLD << BLUE << "real graph"
    << RESET " you would like to load or " << RED << BOLD << "[0]" << RESET << " to "
    << BOLD << RED << "go back" << RESET << "\n" << endl;

    footer();

    int option = readOption(3);

    if (option == 0) startMenu();
    else {
        manager.loadRealGraph(option);
        mainMenu();
    };
}

void Interface::loadExtraGraphMenu() {
    clear();
    header();

    cout << "\t Enter the number of " << BOLD << BLUE << "nodes" << RESET << " to load the"
    << BOLD << BLUE << " extra graph " << RESET << "with or"
    << BOLD << RED << " [0] " << RESET <<  "to" << BOLD << RED << " go back" << endl;
    cout << BOLD << YELLOW << "\n\t Node Options: " << RESET << "25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900";

    footer();

    int option = readNodeNumber();

    if (option == 0) startMenu();
    else {
        manager.loadExtraGraph(option);
        mainMenu();
    }
}

void Interface::triangularHeuristicMenu() {
    clear();
    header();

    cout << "\tWhat would you like to" << BOLD << BLUE <<  " do?\n" << RESET << endl
    << BOLD << BLUE << "\t[1]" << RESET << " - Run Triangular Heuristics Algorithm" << endl
    << BOLD << BLUE << "\t[2]" << RESET << " - Run Comparison with Backtracking Algorithm" << endl
    << BOLD << RED << "\t[0]" << RESET << " - Back" << endl;

    footer();
    int option = readOption(2);

    switch(option) {
        case 1:
            printTriangularInequality(false);
            break;
        case 2:
            printTriangularInequality(true);
            break;
        case 0:
            mainMenu();
    }

    triangularHeuristicMenu();
}

void Interface::otherHeuristicMenu() {
    clear();
    header();

    cout << "\tWhat would you like to" << BOLD << BLUE <<  " do?\n" << RESET << endl
         << BOLD << BLUE << "\t[1]" << RESET << " - Run ??? Heuristics Algorithm" << endl
         << BOLD << BLUE << "\t[2]" << RESET << " - Run Comparison with Triangular Inequality Algorithm" << endl
         << BOLD << RED << "\t[0]" << RESET << " - Back" << endl;

    footer();
    int option = readOption(2);

    switch(option) {
        case 1:
            printOtherHeuristic(false);
            break;
        case 2:
            printOtherHeuristic(true);
            break;
        case 0:
            mainMenu();
    }

    otherHeuristicMenu();
}

void Interface::christofidesMenu() {
    clear();
    header();

    cout << GREEN << BOLD << "\tRunning Christofides Algorithm..." << RESET << endl;
    long duration; double cost;
    manager.christofidesTSP(duration, cost);
    cout << BOLD << YELLOW << "\n\n\tRuntime: " << RESET << duration << " ms" << endl;
    cout << BOLD << YELLOW << "\tTour Cost: " << RESET << cost << endl;

    footer();
    inputWait();
    mainMenu();
}

void Interface::realWorldGraphsMenu() {
    clear();
    header();

    cout << "\n\t\t    Insert the" << BOLD << BLUE << " start node " << RESET << "for the" << BOLD << BLUE << " TSP "
    << RESET << "or" << BOLD << RED << " [-1] " << RESET << "to" << BOLD << RED << " go back" << RESET << endl;

    footer();
    int option = readVertex();

    if (option == -1) mainMenu();
    else {
        printRealWorldHeuristic(option);
        realWorldGraphsMenu();
    }
}

void Interface::printBacktracking() {
    clear();
    header();

    cout << GREEN << BOLD << "\tRunning Backtracking Algorithm..." << RESET << endl;
    long duration; double cost;
    std::vector<int> path = manager.backtracking(duration, cost);
    cout << BOLD << YELLOW << "\n\n\tRuntime: " << RESET << duration << " ms" << endl;
    cout << BOLD << YELLOW << "\tTour Cost: " << RESET << cost << endl;

    if (path.size() < 10 || readPath()) printPath(path);

    footer();
    inputWait();
}

void Interface::printRealWorldHeuristic(int option) {
    clear();
    header();

    cout << GREEN << BOLD << "\tRunning Nearest Neighbor Heuristic..." << RESET << endl;
    long duration; double cost;
    std::vector<int> path = manager.realWorldHeuristic(option, duration, cost);
    cout << BOLD << YELLOW << "\n\n\tRuntime: " << RESET << duration << " ms" << endl;
    cout << BOLD << YELLOW << "\tTour Cost: " << RESET << cost << endl;

    if (path.size() < 10 || readPath()) printPath(path);

    footer();
    inputWait();
}

void Interface::printTriangularInequality(bool compare) {
    clear();
    header();

    long duration; double cost;

    cout << GREEN << BOLD << "\tRunning Triangular Inequality Heuristic..." << RESET << endl;
    manager.triangularInequality(duration, cost);
    cout << BOLD << YELLOW << "\n\n\tRuntime: " << RESET << duration << " ms" << endl;
    cout << BOLD << YELLOW << "\tTour Cost: " << RESET << cost << endl;

    if (compare) {
        cout << GREEN << BOLD << "\n\n\tRunning Backtracking Algorithm..." << RESET << endl;
        manager.backtracking(duration, cost);
        cout << BOLD << YELLOW << "\n\n\tRuntime: " << RESET << duration << " ms" << endl;
        cout << BOLD << YELLOW << "\tTour Cost: " << RESET << cost << endl;
    }

    footer();
    inputWait();
}

void Interface::printOtherHeuristic(bool compare) {
    clear();
    header();

    long duration; double cost;

    cout << GREEN << BOLD << "\tRunning ???? Heuristic..." << RESET << endl;
    std::vector<int> path = manager.realWorldHeuristic(0, duration, cost); // manager.otherHeuristic
    cout << BOLD << YELLOW << "\n\n\tRuntime: " << RESET << duration << " ms" << endl;
    cout << BOLD << YELLOW << "\tTour Cost: " << RESET << cost << endl;

    if (compare) {
        cout << GREEN << BOLD << "\n\n\tRunning Triangular Inequality Algorithm..." << RESET << endl;
        manager.triangularInequality(duration, cost);
        cout << BOLD << YELLOW << "\n\n\tRuntime: " << RESET << duration << " ms" << endl;
        cout << BOLD << YELLOW << "\tTour Cost: " << RESET << cost << endl;
    } else {
        if (path.size() < 10) printPath(path);
    }

    footer();
    inputWait();
}

void Interface::printPath(std::vector<int> path) {
    cout << BOLD << YELLOW << "\n\tFound Path: \n\n\t" << RESET;

    int count = 0;
    for (int i : path) {
        count++;
        cout << BOLD << " -> " << BLUE << i << RESET;
        if (count % 10 == 0) cout << "\n\t";
    }
}
