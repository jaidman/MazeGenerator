#include "maze.h"
#include <iostream>
#include <fstream>
#include <ostream>
#include <vector>


int main(int argc, char *argv[]) {
    std::string fname = argv[4];
    int seed = std::stoi(argv[1]);
    std::srand(seed);
    int row = std::stoi(argv[2]);
    int col = std::stoi(argv[3]);
    Maze grid(row, col);

    grid.generateMaze(row, col, seed);

    grid.printMaze(fname);
}
