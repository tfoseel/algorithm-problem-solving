// BOJ 6549. 히스토그램에서 가장 큰 직사각형

#include <cstdio>
#include <vector>
#include <algorithm>

long long solve(std::vector<long long> &hist, long long lo, long long hi) {
    // Base case
    if (lo > hi) return 0;
    if (lo == hi) return hist[lo];
    // Brute-force approach for small input.
    if (hi - lo <= 100) {
        long long result {-1};
        for (long long size = 1; size <= hi - lo + 1; size++) {
            for (long long i = lo; i <= hi; i++) {
                long long j = i + size - 1;
                if (j > hi) continue;
                long long area = size * (*std::min_element(hist.begin() + i, hist.begin() + j + 1));
                result = std::max(result, area);
            }
        }
        return result;
    }
    long long mid {(lo + hi) / 2};
    // Case 1: The rectangle with maximum area is on the left half or right half.
    long long result = std::max(solve(hist, lo, mid), solve(hist, mid + 1, hi));
    // Case 2: It lies both on the left and right half.
    // Starting from hist[mid] and hist[mid + 1], 
    // extend the rectangle to the direction of larger hist value.
    long long i {mid}; long long j {mid + 1}; long long h {std::min(hist[i], hist[j])};
    while (i >= lo || j <= hi) {
        result = std::max(result, (j - i + 1) * h);
        if (i == lo && j == hi) break;
        if (i == lo) {
            j++;
            h = std::min(h, hist[j]);
        } else if (j == hi) {
            i--;
            h = std::min(h, hist[i]);
        } else if (hist[i - 1] >= hist[j + 1]) {
            i--;
            h = std::min(h, hist[i]);
        } else if (hist[i - 1] < hist[j + 1]) {
            j++;
            h = std::min(h, hist[j]);
        }
    }
    return result; 
}

int main() {
    while (1) {
        int n;
        std::vector<long long> hist;
        // Input
        scanf("%d", &n);
        if (n == 0) break;
        for (int i=0; i<n; i++) {
            long long h;
            scanf("%lld", &h);
            hist.push_back(h);
        }
        // Output
        printf("%lld\n", solve(hist, 0, n - 1));
    }
    return 0;
}