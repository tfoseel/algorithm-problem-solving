// BOJ 2505. 두 번 뒤집기

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

// For test.
#include <random>

void flip(std::vector<int> &v, int i, int j) {
    std::vector<int> tmp;
    for (int k=0; k<v.size(); k++) {
        if (i <= k && k <= j) tmp.push_back(v[i + j - k]);
        else tmp.push_back(v[k]);
    }
    v.clear();
    v = tmp;
}

int solve(std::vector<int> &v) {
    // Find indices i, where |v[i] - v[i - 1]| != 1. Let the indices be unique_indices.
    // Since there are two flips, there will be at most 4 unique_indices.
    // However, a flip can happen either before or after unique_indices,
    // so let's add the adjacent indice of unique_indices for a candidate.
    // Then there will be at most 8 candidates.
    std::vector<int> unique_indices_1;
    for (int i=1; i<v.size(); i++)
        if (v[i] - v[i - 1] != -1 && v[i] - v[i - 1] != 1) {
            unique_indices_1.push_back(i);
            if (i + 1 < v.size()) unique_indices_1.push_back(i + 1);
        }
    std::sort(unique_indices_1.begin(), unique_indices_1.end());
    if (unique_indices_1.empty()) {
        // Trivial base case.
        std::cout << "1 1\n1 1" << std::endl;
    } else if (unique_indices_1.size() == 2) {
        // If the size of 'unique_indices_1' is 2, then answer is [unique_indices[0], unique_indices[1] - 1].
        flip(v, unique_indices_1[0], unique_indices_1[1] - 1);
        std::cout << unique_indices_1[0] << " " << unique_indices_1[1] - 1 << std::endl;
        std::cout << "1 1" << std::endl;
        return 0;
    } else {
        // Given unique indices, choose 2 and flip.
        // If there are 2 unique indices after flip, then flip with these 2 unique indices to get answer.
        // If not, restore the vector and try with other pair.
        std::vector<int> filter (unique_indices_1.size() - 2, -1);
        filter.push_back(0);
        filter.push_back(0);
        do {
            // Choose 2 indices and flip.
            int i1 {-1}, j1 {-1};
            for (int k=0; k<filter.size(); k++) {
                if (filter[k] == 0 && i1 == -1) i1 = unique_indices_1[k];
                if (filter[k] == 0 && i1 != -1) j1 = unique_indices_1[k];
            }
            flip(v, i1, j1 - 1);
            // Count unique indices.
            std::vector<int> unique_indices_2;
            for (int i=1; i<v.size(); i++)
                if (v[i] - v[i - 1] != -1 && v[i] - v[i - 1] != 1) unique_indices_2.push_back(i);
            std::sort(unique_indices_2.begin(), unique_indices_2.end());
            // If there are two unique indices, then flip with them to get answer.
            // Otherwise restore and try again.
            if (unique_indices_2.size() == 2) {
                flip(v, unique_indices_2[0], unique_indices_2[1] - 1);
                std::cout << i1 << " " << j1 - 1 << std::endl;
                std::cout << unique_indices_2[0] << " " << unique_indices_2[1] - 1 << std::endl;
                return 0;
            } else {
                flip(v, i1, j1 - 1);
            }
        } while (std::next_permutation(filter.begin(), filter.end()));
    }
    return -1;
}

void test() {
    std::cout << "TEST STARTS..." << std::endl;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dis(5, 30);
    int test_counter {0};
    while (1) {
        int n = dis(gen);
        std::uniform_int_distribution<int> r(1, n - 1);
        std::vector<int> vec {0};
        for (int i=1; i<=n; i++) vec.push_back(i);
        vec.push_back(n + 1);
        int i1, j1, i2, j2;
        {
            int i = r(gen); int j = r(gen);
            i1 = std::min(i, j); j1 = std::max(i, j);
            i = r(gen); j = r(gen);
            i2 = std::min(i, j); j2 = std::max(i, j);
        }
        flip(vec, i1, j1); flip(vec, i2, j2);
        std::cout << "\nTEST " << ++test_counter << ".\nvec: ";
        for (int i=1; i<vec.size() - 1; i++) std::cout << vec[i] << " ";
        std::cout << std::endl;
        if (solve(vec) != 0) {
            std::cout << "ANSWER : [" << i2 << ", " << j2 << "] -> [" << i1 << ", " << j1 << "]" << std::endl;
            std::cout << "TEST FAILED" << std::endl;
            break;
        } else {
            std::cout << "TEST PASSED" << std::endl;
        }
    }
}

const int TEST = 1;
const int SOLVE = 2;

int main() {
    int MODE = SOLVE;
    if (MODE == TEST) {
        test();
    } else if (MODE == SOLVE) {
        int n;
        // Adding v[0] = 0 and v[n + 1] = n + 1 does not affect the answer.
        std::vector<int> vec {0};
        // Input
        std::cin >> n;
        for (int i=0; i<n; i++) {
            int x;
            std::cin >> x;
            vec.push_back(x);
        }
        vec.push_back(n + 1);
        solve(vec);
    }
    return 0;
}