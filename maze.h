#ifndef MAZE_H
#define MAZE_H
#include <cstdlib> // For std::rand() and std::srand()
#include <vector>
#include <string>

struct cell {
    std::string wall;
    bool visited;
    int row, col;

    cell(std::string wall, bool visited, int row, int col);
};


class Maze {
private:
    int row;
    int col;

public:
    std::vector<std::vector<cell> > grid;

    std::vector<cell> neighbors(int row, int col);

    void printMaze(std::string fname);

    std::vector<std::vector<int> > getNeighbors(int row, int col, int curRow, int curCol,
                                                std::vector<std::vector<cell> > &grid);

    Maze(int row, int col);

    void generateMaze(int row, int col, int seed);
};

#endif // MAZE_H
