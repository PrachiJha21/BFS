#ifndef GRID_H
#define GRID_H

#include <vector>
#include "Node.h"

class Grid {
public:
    int rows, cols, cellSize;
    std::vector<std::vector<int>> grid;

    Node start{-1,-1};
    Node end{-1,-1};

    Grid(int r, int c, int size);

    bool isValid(int r, int c);
    void clearSearch();
};

#endif
