// BOJ 14003. 가장 긴 증가하는 부분 수열 5

#include <cstdio>
#include <vector>
#include <algorithm>

std::vector<int> seq;

// A vector to keep track on the length of LIS.
std::vector<int> lis_elements;
// A vector to keep track on the result of lower_bound().
std::vector<int> lis_indices;
// A vector to build answer from lis_indices.
std::vector<int> answer;

int main() {
    int n;
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
            // seq[i] can be a new element of LIS, so attach to lis_elements.
            lis_indices.push_back(lis_elements.size());
            lis_elements.push_back(seq[i]);
        } else {
            // If seq[i] < lis_elements[pos], seq[i] can replace lis_elements[pos]
            // to have more possibility to increase length of LIS.
            int pos = std::lower_bound(lis_elements.begin(), lis_elements.end(), seq[i]) - lis_elements.begin();
            lis_indices.push_back(pos);
            lis_elements[pos] = seq[i];
        }
    }
    // The length of lis_elements is the length of LIS
    // since we increased the length of lis_elements only when new element is larger than max(lis_elements).
    // However, elements in lis_elements may not be elements of LIS,
    // since we did not keep order when replacing.
    // From the end of vector, we add first-seen elements of
    // index lis_elements.size() - 1, lis_elements.size() - 2...
    // to build LIS of length lis_elements.size() preserving order.
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