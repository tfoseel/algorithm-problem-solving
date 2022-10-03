#include <iostream>
#include <vector>
#include <queue>

// A 2D vector representing an adjacency list of a graph.
std::vector<std::vector<int, int>> graph;
// An 1D vector to check if a vertex is visited in O(1) time.
std::vector<bool> visited;

// v is the index of vertice to visit.

// Depth-first-search algorithm.
void DFS(int v) {
    if (visited[v]) return;
	// Mark the vertice as visited and do something.
    visited[v] = true;
	// std::cout << v << std::endl;
    for (auto i: graph[v]) DFS(i);
}

// Breadth-first-search algorithm.
void BFS(int v) {
    std::queue<int> q;
    // Mark the inital vertice as visited and push to the queue.
    visited[v] = true;
    q.push(v);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
		// Do something here.
        // std::cout << u << std::endl;
        for (auto i: graph[v]) {
            if (!visited[i]) {
				// Mark the vertice as visited and push to the queue.
                visited[i] = true;
                q.push(i);
            }
		}
    }
}