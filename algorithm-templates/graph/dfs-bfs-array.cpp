#include <iostream>
#include <vector>
#include <queue>

const int ARR_SIZE {1000};

// A 2D array representing an adjacency matrix of a graph.
int graph[ARR_SIZE][ARR_SIZE];
// An 1D array to check if a vertex is visited in O(1) time.
bool visited[ARR_SIZE];

// v is the index of vertice to visit, and n is the number of vertices.

// Depth-first-search algorithm.
void DFS(int v, int n) {
    if (visited[v]) return;
    // Mark the vertice as visited and do something.
    visited[v] = true;
    // std::cout << u << std::endl;
    for (int i=0; i<n; i++) {
        if (graph[v][i] == 1) DFS(i, n);
    }
}

// Breadth-first-search algorithm.
void BFS(int v, int n) {
    std::queue<int> q;
    // Mark the inital vertice as visited and push to the queue.
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // Do something here.
        // std::cout << u << std::endl;
        for (int i=1; i<=n; i++) {
            if (graph[u][i] == 1 && !visited[i]) {
                // Mark the vertice as visited and push to the queue.
                visited[i] = true;
                q.push(i);
            }
        }
    }
}