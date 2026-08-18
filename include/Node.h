#ifndef NODE_H
#define NODE_H

struct Node {
    int row, col;

    Node(int r = 0, int c = 0) {
        row = r;
        col = c;
    }

    bool operator==(const Node& other) const {
        return row == other.row && col == other.col;
    }
};

#endif
