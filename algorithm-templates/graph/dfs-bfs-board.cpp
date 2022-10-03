#include <iostream>
#include <vector>
#include <queue>

const int BOARD_SIZE {1000};

// A 2D array representing board.
int board[BOARD_SIZE][BOARD_SIZE];
// An 2D array to check if a vertex is visited in O(1) time.
bool visited[BOARD_SIZE][BOARD_SIZE];

// Returns next vertices can be visited. 
std::vector<std::pair<int, int>> next(std::pair<int, int> v, int m, int n) {
    return std::vector<std::pair<int, int>> {};
}

// v is the position of vertice to visit, and m×n is the size of board.

// Depth-first-search algorithm.
void DFS(std::pair<int, int> v, int m, int n) {
    if (visited[v.first][v.second]) return;
    // Mark the vertice as visited and do something.
    visited[v.first][v.second] = true;
    // std::cout << v.first << " " << v.second << std::endl;
    for (auto p: next(v, m, n)) DFS(p, m, n);
}

// Breadth-first-search algorithm.
void BFS(std::pair<int, int> v, int m, int n) {
    std::queue<std::pair<int, int>> q;
    // Mark the inital vertice as visited and push to the queue.
    visited[v.first][v.second] = true;
    q.push(v);
    while (!q.empty()) {
        auto u = q.front();
        q.pop();
        // Do something here.
        // std::cout << u.first << " " << u.second << std::endl;
        for (auto p: next(u, m, n)) {
            if (!visited[p.first][p.second]) {
                // Mark the vertice as visited and push to the queue.
                visited[p.first][p.second] = true;
                q.push(p);
            }
        }
    }
}