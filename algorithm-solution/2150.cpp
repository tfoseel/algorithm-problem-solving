// BOJ 2150. Strongly Connected Component

#include <cstdio>
#include <vector>
#include <stack>
#include <algorithm>

int v, e;
std::vector<std::vector<int>> answer;

// A counter variable for storing order of visit.
int visit_order {1};
// Graph represented by adjacency list.
std::vector<std::vector<int>> graph;
// visited[i] = 0 if not visited, else stores visited order.
std::vector<int> visited;
// Stores if the SCC is determined.
std::vector<bool> finished;
// A stack for finding SCC.
std::stack<int> stack;

// Find SCC of the graph with Tarjan's algorithm.
int dfs(int v) {
    int parent = visit_order;
    visited[v] = visit_order++;
    stack.push(v);
    for (int i: graph[v]) {
        if (visited[i] == 0) {
            parent = std::min(parent, dfs(i));
        } else if (!finished[i]) {
            // Found a cycle.
            parent = std::min(parent, visited[i]);
        }
    }
    // If vertex v is visited first among vertices forming a cycle,
    // pop vertices from stack until v is popped.
    if (parent == visited[v]) {
        std::vector<int> scc;
        while (1) {
            int u = stack.top();
            stack.pop();
            finished[u] = true;
            scc.push_back(u);
            if (u == v) break;
        }
        answer.push_back(scc);
    }
    return parent;
}

int main() {
    // Input
    scanf("%d %d", &v, &e);
    for (int i=0; i<v; i++) {
        graph.push_back(std::vector<int>());
        visited.push_back(false);
        finished.push_back(false);
    }
    for (int i=0; i<e; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        // Vertex index starts from 1 in the problem.
        x--; y--;
        graph[x].push_back(y);
    }
    // Solve
    for (int i=0; i<v; i++)
        if (!finished[i]) dfs(i);
    for (auto &scc: answer) std::sort(scc.begin(), scc.end());
    std::sort(answer.begin(), answer.end());
    // Output
    printf("%d\n", answer.size());
    for (auto scc: answer) {
        for (int i: scc) printf("%d ", i + 1);
        printf("-1\n");
    }
    return 0;
}