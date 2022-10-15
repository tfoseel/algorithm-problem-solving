// BOJ 14003. 가장 긴 증가하는 부분 수열 5

#include <cstdio>
#include <vector>
#include <algorithm>

const int NEG_INF {-1'000'000'001};

int main() {
    int n;
    std::vector<int> seq;
    std::vector<int> lis_elements;
    std::vector<int> lis_indices;
    std::vector<int> answer;
    // Input
    scanf("%d", &n);
    for (int i=0; i<n; i++) {
        int x;
        scanf("%d", &x);
        seq.push_back(x);
    }
    // Solve
    for (int i=0; i<n; i++) {
        if (lis_elements.empty() || seq[i] > lis_elements[lis_elements.size() - 1]) {
            lis_indices.push_back(lis_elements.size());
            lis_elements.push_back(seq[i]);
        } else {
            int pos = std::lower_bound(lis_elements.begin(), lis_elements.end(), seq[i]) - lis_elements.begin();
            lis_indices.push_back(pos);
            lis_elements[pos] = seq[i];
        }
    }
    int lis_index = lis_elements.size() - 1;
    for (int i=lis_indices.size() - 1; i>=0; i--) {
        if (lis_indices[i] == lis_index) {
            answer.push_back(seq[i]);
            lis_index--;
        }
    }
    std::sort(answer.begin(), answer.end());
    // Output
    printf("%d\n", lis_elements.size());
    for (int i: answer) printf("%d ", i);
    return 0;
}