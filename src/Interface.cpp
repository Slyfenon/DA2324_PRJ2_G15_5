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

int Interface::readEdgeNumber() {
    string option;
    do {
        cout << BOLD << BLUE << "\n\tEdge Number: " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (false); // manager.validateEdgeNumber()

    return stoi(option);
}

int Interface::readVertex() {
    string option;
    do {
        cout << BOLD << BLUE << "\n\tVertex: " << RESET;
        cin.clear();
        cin >> option;
        cin.ignore();
    } while (false); // manager.validateVertex()

    return stoi(option);
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
         << BOLD << BLUE << "\t[3]" << RESET << " - Other Sus Heuristic" << endl
         << BOLD << BLUE << "\t[4]" << RESET << " - Arbitrary Starting Point" << endl
         << BOLD << RED << "\t[0]" << RESET << " - Back" << endl;

    footer();

    int option = readOption(4);

    switch(option) {
        case 1:
            printBacktracking();
            break;
        case 2:
            manager.triangularInequality();
            triangularHeuristicMenu();
            break;
        case 3:
            otherHeuristicMenu();
            break;
        case 4:
            realWorldGraphsMenu();
            break;
        case 0:
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

    cout << "\t Enter the number of " << BOLD << BLUE << "edges" << RESET << " to load the"
    << BOLD << BLUE << " extra graph " << RESET << "with or"
    << BOLD << RED << " [0] " << RESET <<  "to" << BOLD << RED << " go back" << endl;
    cout << BOLD << YELLOW << "\n\t Edge Options: " << RESET << "25, 50, 75, 100, 200, 300, 400, 500, 600, 700, 800, 900";

    footer();

    int option = readEdgeNumber();

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
            // manager.triangularHeuristics
            // printPath
            break;
        case 2:
            // manager.triangularHeuristics
            // printMetrics
            // manager.backtracking
            // printMetrics
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
         << BOLD << BLUE << "\t[1]" << RESET << " - Run Sus Heuristics Algorithm" << endl
         << BOLD << BLUE << "\t[2]" << RESET << " - Run Comparison with Backtracking Algorithm" << endl
         << BOLD << RED << "\t[0]" << RESET << " - Back" << endl;

    footer();
    int option = readOption(2);

    switch(option) {
        case 1:
            // manager.susHeuristics
            // printPath
            break;
        case 2:
            // manager.susHeuristics
            // printMetrics
            // manager.backtracking
            // printMetrics
            break;
        case 0:
            mainMenu();
    }

    otherHeuristicMenu();
}

void Interface::realWorldGraphsMenu() {
    clear();
    header();

    cout << "\n\t\t    Insert the" << BOLD << BLUE << " start node " << RESET << "for the" << BOLD << BLUE << " TSP "
    << RESET << "or" << BOLD << RED << " [0] " << RESET << "to" << BOLD << RED << " go back" << RESET << endl;

    footer();
    int option = readVertex();

    if (option == 0) mainMenu();
    else {
        // manager.realWorldTSP(option)
        // printPath
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

    footer();

    // Enable path only sometimes??
    cout << "\n\n\tThe Path";
    for (auto v : path) cout << " -> " << v;

    inputWait();
}
