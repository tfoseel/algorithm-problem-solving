// BOJ 2152. 여행 계획 세우기

#include <cstdio>
#include <vector>
#include <set>
#include <stack>

int n, m, s, t;

// Variables for finding SCC of a graph.

// A vector of vector stores SCC of graph.
std::vector<std::vector<int>> sccs;
// A counter variable for storing order of visit and SCC group.
int visit_order {1}; int group_number {0};
// Graph represented by adjacency list.
std::vector<std::vector<int>> graph;
// visited[i] = 0 if not visited, else stores visited order.
std::vector<int> visited;
// Stores if the SCC is determined.
// finished[i] = -1 if not determined, else stores which group vertice i is in.
std::vector<int> finished;
// A stack for finding SCC.
std::stack<int> stack;

// Variables to build a metagraph.
// Each vertex indicates one SCC of original graph.
std::vector<std::set<int>> metagraph;
std::vector<bool> meta_visited;
std::vector<int> scc_size;
std::vector<int> dp;

// Find SCC of a graph using Tarjan's algorithm.
int find_scc(int v) {
    int parent = visit_order;
    visited[v] = visit_order++;
    stack.push(v);
    for (int i: graph[v]) {
        if (visited[i] == 0) {
            parent = std::min(parent, find_scc(i));
        } else if (finished[i] == -1) {
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
            finished[u] = group_number;
            scc.push_back(u);
            if (u == v) break;
        }
        sccs.push_back(scc);
        group_number++;
    }
    return parent;
}

// Traverse DFS and get maximum value.
int dfs(int v, int acc) {
    // Reached to SCC which contains original vertex t.
    if (v == finished[t]) return acc + sccs[v].size();
    int result {0};
    meta_visited[v] = true;
    for (int i: metagraph[v]) {
        if (!meta_visited[i]) {
            result = std::max(result, dfs(i, acc + sccs[v].size()));
        }
    }
    return result;
}

int main() {
    // Input
    scanf("%d %d %d %d", &n, &m, &s, &t);
    s--; t--;
    for (int i=0; i<n; i++) {
        graph.push_back(std::vector<int>());
        visited.push_back(false);
        finished.push_back(-1);
    }
    for (int i=0; i<m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        // Vertex index starts from 1 in the problem.
        x--; y--;
        graph[x].push_back(y);
    }
    // Solve
    // Find SCC of the graph.
    for (int i=0; i<n; i++)
        if (finished[i] == -1) find_scc(i);
    // Build vertices of a metagraph.
    for (int i=0; i<sccs.size(); i++) {
        metagraph.push_back(std::set<int>());
        meta_visited.push_back(false);
        dp.push_back(-1);
    }
    // Insert edges to the metagraph.
    for (int i=0; i<n; i++) {
        for (int j: graph[i]) {
            // Edge i -> j in original graph is edge finished[i] -> finished[j] in metagraph.
            if (finished[i] != finished[j]) metagraph[finished[i]].insert(finished[j]);
        }
    }
    // Re-define s and t for being used in metagraph.
    s = finished[s]; t = finished[t];
    // Since we used Tarjan's algorithm,
    // indices of sccs indicates the reversed order of topological sort of metagraph.
    dp[s] = sccs[s].size();
    for (int i=s; i>=t; i--) {
        if (dp[i] == -1) continue;
        for (int j: metagraph[i]) {
            dp[j] = std::max(dp[j], dp[i] + (int)sccs[j].size());
        }
    }
    // Output
    printf("%d\n", dp[t]);
    return 0;
}