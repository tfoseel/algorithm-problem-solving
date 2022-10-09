// BOJ 2618. 경찰차

#include <iostream>
#include <cmath>
#include <vector>

const int INF {999999999};

int n, w;
// cases[i] is the place of case i.
// cases[0] is a special state, where car 1 and car 2 are on starting point (0, 0), (n - 1, n - 1).
std::vector<std::pair<int, int>> cases {std::make_pair(-1, -1)};

// dp[i][j] is the remaining distance,
// where car 1 is at the place of case i and car 2 is at the place of case j.
int dp[1001][1001];

// Returns the distance between two places where case a and b occured.
int dist(std::pair<int, int> a, std::pair<int, int> b) {
    return std::abs(a.first - b.first) + std::abs(a.second - b.second);
}

int solve(int i, int j) {
    // Memoization
    if (dp[i][j] != INF) return dp[i][j];
    // Let the index of next case to visit be k.
    int k = std::max(i, j) + 1;
    // Get positions of car 1 and car 2.
    auto car1 = (i == 0) ? std::make_pair(0, 0) : cases[i];
    auto car2 = (j == 0) ? std::make_pair(n - 1, n - 1) : cases[j];
    // Either car 1 or car 2 can visit the case k.
    int car1_dist = dist(car1, cases[k]) + solve(k, j);
    int car2_dist = dist(cases[k], car2) + solve(i, k);
    if (car1_dist < car2_dist) dp[i][j] = car1_dist; 
    else dp[i][j] = car2_dist;
    return dp[i][j];
}

void print_path(int i, int j) {
    // End of printing.
    if (i == w || j == w) return;
    // Find choices that makes the minimum distance in similar way of function 'solve'.
    // However, there's no recursion of 'solve' since we already stored all values in array 'dp'.
    int k = std::max(i, j) + 1;
    auto car1 = (i == 0) ? std::make_pair(0, 0) : cases[i];
    auto car2 = (j == 0) ? std::make_pair(n - 1, n - 1) : cases[j];
    int car1_dist = dist(car1, cases[k]) + solve(k, j);
    int car2_dist = dist(cases[k], car2) + solve(i, k);
    if (car1_dist < car2_dist) {
        std::cout << 1 << std::endl;
        print_path(k, j);
    } else {
        std::cout << 2 << std::endl;
        print_path(i, k);
    }
}

int main() {
    // Input
    std::cin >> n >> w;
    for (int i=0; i<w; i++) {
        int y, x;
        std::cin >> y >> x;
        cases.push_back(std::make_pair(y - 1, x - 1));
    }
    // Initialization for dynamic programming.
    for (int i=0; i<=w; i++)
        for (int j=0; j<w; j++) dp[i][j] = INF;
    for (int i=0; i<=w; i++) {
        dp[w][i] = 0;
        dp[i][w] = 0;
    }
    // Output
    std::cout << solve(0, 0) << std::endl;
    print_path(0, 0);
    return 0;
}