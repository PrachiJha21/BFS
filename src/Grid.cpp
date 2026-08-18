#include "../include/Grid.h"

Grid::Grid(int r, int c, int size)
    : rows(r), cols(c), cellSize(size) {

    grid.assign(rows, std::vector<int>(cols, 0));
}

bool Grid::isValid(int r, int c) {
    return r >= 0 && r < rows &&
           c >= 0 && c < cols &&
           grid[r][c] != 1;
}

void Grid::clearSearch() {
    for (auto& row : grid)
        for (auto& cell : row)
            if (cell == 2 || cell == 3)
                cell = 0;
}
