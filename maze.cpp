#include "maze.h"

#include <iostream>
#include <ostream>
#include <fstream>
#include <utility>

// Default maze object
Maze::Maze(int newRow, int newCol) {
    this->row = newRow;
    this->col = newCol;
    for (int i = 0; i < row; i++) {
        std::vector<cell> temp;
        for (int j = 0; j < col; j++) {
            cell mycell("1111", false, i, j);
            temp.push_back(mycell);
        }
        grid.push_back(temp);
    }
    // initalizing first cell as 0,0
    grid[0][0].wall[0] = '0';
    grid[row - 1][col - 1].wall[1] = '0';
}

// Default valuues for cell object.
cell::cell(std::string wall, bool visited, int row, int col) {
    this->wall = wall;
    this->visited = visited;
    this->row = row;
    this->col = col;
}

// Gets neighbors in matrix based on current maze parameters, using bound checking
std::vector<std::vector<int> > Maze::getNeighbors(int row, int col, int curRow, int curCol,
                                                  std::vector<std::vector<cell> > &maze) {
    //get all the valid neighbors of a cell
    std::vector<std::vector<int> > neighbors;

    // Check North
    if (curRow - 1 >= 0 && !(maze[curRow - 1][curCol].visited)) {
        neighbors.push_back({curRow - 1, curCol});
    }
    // Check South
    if (curRow + 1 < row && !(maze[curRow + 1][curCol].visited)) {
        neighbors.push_back({curRow + 1, curCol});
    }
    // Check East
    if (curCol + 1 < col && !(maze[curRow][curCol + 1].visited)) {
        neighbors.push_back({curRow, curCol + 1});
    }
    // Check West
    if (curCol - 1 >= 0 && !(maze[curRow][curCol - 1].visited)) {
        neighbors.push_back({curRow, curCol - 1});
    }

    return neighbors;
}

// Checking directions of given matrix
int getdir_index(int row, int col, int r2, int c2, int maxRow, int maxCol) {
    // checks north
    if (row - 1 >= 0 && row - 1 == r2) {
        return 0;
    }
    // check south
    if (row + 1 < maxRow && row + 1 == r2) {
        return 1;
    }
    // check east
    if (col + 1 < maxCol && col + 1 == c2) {
        return 2;
    }
    // check south
    if (col - 1 >= 0 && col - 1 == c2) {
        return 3;
    }
    //the north side of cord1s wall is the south side of cord2s wall hint

    return 0;
}


void Maze::generateMaze(int row, int col, int seed) {
    std::srand(seed);
    // 'A' vector
    std::vector<std::vector<int> > cords;

    // marking first cell as visited
    grid[0][0].visited = true;

    //pushing back the coordinates of first cell into cords vector
    cords.push_back({grid[0][0].row, grid[0][0].col});

    while (!cords.empty()) {
        // vector of current cell's coordinates
        std::vector<int> current;

        // set current to last cords in vector and remove it
        current = cords.back();
        cords.pop_back();

        // create a 2d vector of neighbors
        std::vector<std::vector<int> > neighbors;
        neighbors = getNeighbors(row, col, current[0], current[1], grid);

        if (!neighbors.empty()) {
            cords.push_back(current);

            // generate random index
            int index = std::rand() / ((RAND_MAX + 1u) / neighbors.size());

            // assign index to a new vector of chosenNeighors, will use for getting directions
            std::vector<int> chosenNeighbor = neighbors[index];

            // Choose indexes based on information in current maze and chosenNeighbor maze.
            int index1 = getdir_index(current[0], current[1], chosenNeighbor[0], chosenNeighbor[1], grid.size(),
                                      grid[0].size());
            int index2 = getdir_index(chosenNeighbor[0], chosenNeighbor[1], current[0], current[1], grid.size(),
                                      grid[0].size());

            // Marking cells as visited
            grid[chosenNeighbor[0]][chosenNeighbor[1]].wall[index2] = '0';
            grid[current[0]][current[1]].wall[index1] = '0';
            grid[chosenNeighbor[0]][chosenNeighbor[1]].visited = true;
            cords.push_back(chosenNeighbor);
        }
    }
}

// Printing maze to output file
void Maze::printMaze(std::string fname) {
    std::ofstream myfile(fname);
    for (long unsigned int i = 0; i < grid.size(); i++) {
        for (long unsigned int j = 0; j < grid[0].size(); j++) {
            int temp = 1;
            int temp2 = 0;
            for (int k = 0; k < 4; k++) {
                temp2 += (grid[i][j].wall[3 - k] - 48) * temp;
                temp *= 2;
            }
            myfile << temp2 << " ";
        }
        myfile << std::endl;
    }
}
