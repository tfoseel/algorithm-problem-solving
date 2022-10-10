// BOJ 2098. 외판원 순회

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

const int INF {99999999};
int n;

// costs[i][j] is cost to navigate from vertice i to j.
std::vector<std::vector<int>> costs;

// Let C(S, i) be a minimum cost when visiting set of vertices S and terminates at vertice i.
// dp[x] is minimum cost where x.first == (an integer encoding for S) and x.second == i.
std::map<std::pair<int, int>, int> dp;

// Encode string representation of set S to integer.
// For example, when S == {1, 0, 0, 1}, and s == "1001", it returns 9(==1001(2)).
int encode_set(std::string s) {
    int x {0};
    for (int i=0; i<s.size(); i++) x += (1 << (s.size() - 1 - i)) * (s[i] == '1');
    return x;
}

// solve(size) is a process of getting C(S, j) for each vertice j != 0 in S,
// where |S| = size using dynamic programming.
void solve(int size) {
    if (size == 2) {
        // A path consists of one edge.
        for (int i=0; i<n; i++)
            dp[std::make_pair((1 << (n - 1)) + (1 << (n - i - 1)), i)] = costs[0][i];
        return;
    }
    std::string s = std::string(n - size, '0') + std::string(size - 1, '1');
    do {
        // "1" + s is subset of given size, where subset[0] == 1.
        std::string subset = "1" + s;
        // Disallow to return to vertice 0.
        dp[std::make_pair(encode_set(subset), 0)] = INF;
        // For any vertice j != 0 in subset S, get C(S, j) from partial answers C(S - {j}, i).
        for (int j=1; j<subset.size(); j++) {
            if (subset[j] == '0') continue;
            // C(S, j) == min(C(S - {j}, i)) + cost(i, j) where vertice i != 0 is in set S - {j}.
            subset[j] = '0';
            int sub_answer {INF};
            for (int i=1; i<subset.size(); i++) {
                if (subset[i] == '1')  {
                    sub_answer = std::min(
                        sub_answer, dp[std::make_pair(encode_set(subset), i)] + costs[i][j]
                    );
                }
            }
            subset[j] = '1';
            // Store answer of subproblems into map for reuse.
            dp[std::make_pair(encode_set(subset), j)] = sub_answer;
        }
    } while (std::next_permutation(s.begin(), s.end()));
}

int main() {
    // Input
    std::cin >> n;
    for (int i=0; i<n; i++) {
        costs.push_back(std::vector<int>());
        for (int j=0; j<n; j++) {
            int x;
            std::cin >> x;
            if (x == 0) x = INF;
            costs[i].push_back(x);
        }
    }
    // Solve
    dp[std::make_pair(0, 0)] = 0;
    for (int size=2; size<=n; size++) solve(size);
    int answer {INF};
    for (int i=1; i<n; i++)
        answer = std::min(answer, dp[std::make_pair((1 << n) - 1, i)] + costs[i][0]);
    // Output
    std::cout << answer << std::endl;
    return 0;
}