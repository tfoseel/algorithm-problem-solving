#include <iostream>
#include <vector>
#include <queue>

// A graph consists of one or more vertices.
// Usually int(in graph problems) or std::pair<int, int>(in board problems).
using Vertice = int;

// A graph can be an 2D array, 2D std::vector object, etc.
// It can be declared as either global or local variable.
class Graph {

};

// Returns true if the given vertice is already visited.
bool visited(Graph &g, Vertice i) {
    return false;
}

// Returns next vertices can be visited. 
std::vector<Vertice> next(Graph &g, Vertice i) {
    return std::vector<Vertice> {};
}

// Depth-first-search algorithm.
void DFS(Graph &g, Vertice v) {
    if (visited(g, v)) return;
    // Mark the vertice as visited and do something.
    // graph[v][v] = -1, visited[i] = true, etc...
    // std::cout << v << std::endl;
    for (auto i: next(g, v)) DFS(g, i);
}

// Breadth-first-search algorithm.
void BFS(Graph &g, Vertice v) {
    // Variables to keep track of the distances from inital vertex.
    // 'dist' is the distance from inital vertex.
    // int dist {1};
    // 'num_remaining_vertices' is the number of remaining vertex, 'dist' away from inital vertex.
    // int num_remaining_vertices {1};
    std::queue<int> q;
    // Mark the inital vertice as visited and push to the queue.
    // graph[v][v] = -1, visited[v] = true, etc...
    q.push(v);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        // num_remaining_vertices--;
        // Do something here.
        // std::cout << u << std::endl;
        for (auto i: next(g, u)) {
            if (!visited(g, i)) {
                // Mark the vertice as visited and push to the queue.
                // graph[i][i] = -1, visited[i] = true, etc...
                q.push(i);
            }
        }
        // std::cout << dist << std::endl;
        // if (num_dist == 0) {
        //     dist++;
        //     num_remaining_vertices = q.size();
        // }
    }
}