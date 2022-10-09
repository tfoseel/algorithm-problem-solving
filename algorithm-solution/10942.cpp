// BOJ 10942. 팰린드롬?

#include <cstdio>

int arr[2000];

// dp[x][y] stores results of function palindrome(x, y).
// A value of dp[x][y] is 0 if subanswer is not calculated yet, 1 if true, 2 if false.
// The reason for assigning value like this is to save time for initialization.
short dp[2001][2001];

// Returns true if substring s[x...y] of given string is a palindrome.
bool palindrome(int x, int y) {
    // Trivial base case.
    if (y - x <= 0) {
        dp[x][y] = 1;
        return true;
    }
    // Use stored value.
    if (dp[x][y] != 0) return (dp[x][y] == 1);
    // Get an answer from answers of smaller subproblems.
    if (arr[x] == arr[y] && palindrome(x + 1, y - 1)) {
        dp[x][y] = 1;
        return true;
    } else {
        dp[x][y] = 2;
        return false;
    }
    return true;
}

int main() {
    int n, m;
    // Input
    scanf("%d", &n);
    for (int i=0; i<n; i++) scanf("%d", &arr[i]);
    scanf("%d", &m);
    for (int i=0; i<m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        // Given index starts from 1, while array index starts from 0.
        x--; y--;
        // Output
        printf("%d\n", (int)palindrome(x, y));
    }
    return 0;
}