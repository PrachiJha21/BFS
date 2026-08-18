#include "../include/BFS.h"
#include <algorithm>

void BFS::init(Grid& g) {
    done = false;
    visited.clear();
    path.clear();

    used.assign(g.rows, std::vector<bool>(g.cols, false));
    parent.assign(g.rows, std::vector<Node>(g.cols, {-1,-1}));

    while (!q.empty()) q.pop();

    used[g.start.row][g.start.col] = true;
    q.push(g.start);

    start = std::chrono::high_resolution_clock::now();
}

void BFS::step(Grid& g) {
    if (q.empty() || done) return;

    Node cur = q.front(); q.pop();
    visited.push_back(cur);

    if (cur == g.end) {
        done = true;

        Node p = g.end;
        while (!(p == Node(-1,-1))) {
            path.push_back(p);
            p = parent[p.row][p.col];
        }
        std::reverse(path.begin(), path.end());

        distance = path.size() - 1;

        auto end =
            std::chrono::high_resolution_clock::now();

        timeTaken =
            std::chrono::duration<double, std::milli>(
                end - start).count();
        return;
    }

    int dr[4]={-1,1,0,0};
    int dc[4]={0,0,-1,1};

    for(int i=0;i<4;i++){
        int nr=cur.row+dr[i];
        int nc=cur.col+dc[i];

        if(g.isValid(nr,nc) && !used[nr][nc]){
            used[nr][nc]=true;
            parent[nr][nc]=cur;
            q.push({nr,nc});
        }
    }
}

bool BFS::finished() {
    return done;
}
