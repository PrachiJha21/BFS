#ifndef BFS_H
#define BFS_H

#include "Grid.h"
#include <queue>
#include <chrono>

class BFS {
public:
    void init(Grid& grid);
    void step(Grid& grid);
    bool finished();

    double timeTaken = 0;
    int distance = -1;

    std::vector<Node> visited;
    std::vector<Node> path;

private:
    std::queue<Node> q;
    std::vector<std::vector<bool>> used;
    std::vector<std::vector<Node>> parent;

    bool done = false;
    std::chrono::high_resolution_clock::time_point start;
};

#endif
