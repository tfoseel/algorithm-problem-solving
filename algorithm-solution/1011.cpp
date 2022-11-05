// BOJ 1011. Fly me to the Alpha Centauri

#include <iostream>
#include <cmath>

void solve() {
    int x, y;
    // Input
    std::cin >> x >> y;
    // Answer of (x, y) is equal to (0, y - x).
    y -= x;
    x = 0;
    // If max(k_i) = n, then y >= 1 + 2 + ... + n + (n - 1) + ... + 1 = n * n.
    // And it needs (2n - 1) moves.
    int n = (int)std::sqrt(y);
    int moves = 2 * n - 1;
    y -= n * n;
    // y is remaining distance.
    // If y <= n, one additional move of length y can be attached to appropirate position.
    // Otherwise add a move of length n until the remaining distance is less than or equal to n.
    moves += (y / n) + (y % n == 0 ? 0 : 1);
    // Output
    std::cout << moves << std::endl;
}

int main() {
    int T;
    std::cin >> T;
    for (int i=0; i<T; i++) solve();
    return 0;
}