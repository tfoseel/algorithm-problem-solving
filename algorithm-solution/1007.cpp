// BOJ 1007. 벡터 매칭

#define first x
#define second y

#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

typedef std::pair<double, double> Point;

void solve() {
    int n;
    std::vector<Point> vec;
    // Input
    std::cin >> n;
    for (int i=0; i<n; i++) {
        Point p;
        std::cin >> p.x >> p.y;
        vec.push_back(p);
    }
    // Solve
    double answer {999'999'999};
    std::vector<double> sign;
    for (int i = 0; i < vec.size() / 2; i++) sign.push_back(-1);
    for (int i = 0; i < vec.size() / 2; i++) sign.push_back(1);
    do {
        Point vec_sum {0, 0};
        for (int i = 0; i < vec.size(); i++) {
            vec_sum.x += vec[i].x * sign[i];
            vec_sum.y += vec[i].y * sign[i];
        }
        // vec_sum.x * vec_sum.x + vec_sum.y * vec_sum.y can cause overflow.
        // Divide vec_sum by 1000, and mutiply again.
        vec_sum.x /= 1000; vec_sum.y /= 1000;
        answer = std::min(answer, 1000 * std::sqrt(vec_sum.x * vec_sum.x + vec_sum.y * vec_sum.y));
    } while (std::next_permutation(sign.begin(), sign.end()));
    // Output
    std::cout << answer << std::endl;
}

int main() {
    // Set precision of output
    std::cout << std::fixed;
    std::cout.precision(10);
    int T;
    std::cin >> T;
    for (int i=0; i<T; i++) solve();
    return 0;
}