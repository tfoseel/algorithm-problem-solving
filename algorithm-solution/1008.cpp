// BOJ 1018. 제곱 ㄴㄴ 수

#include <iostream>
#include <cmath>
#include <vector>

// Define maximum size of Eratosthenes' seive. sqrt(1,000,000,000,000 + 1,000,000) = 1,000,499.8...
const long long SEIVE_MAX_SIZE {1'000'500};

// Seive to find primes same or less than sqrt(max).
bool seive[SEIVE_MAX_SIZE];
std::vector<long long> primes;
bool filter[1'000'001];

int main() {
    long long min, max;
    // Input
    std::cin >> min >> max;
    // Solve
    // First find primes numbers same or less than sqrt(max).
    seive[0] = false;
    seive[1] = false;
    seive[2] = true;
    for (long long i=3; i*i<=max; i+=2) seive[i] = true;
    for (long long i=3; i*i*i*i<=max; i+=2) {
        if (seive[i])
            for (long long j=3; i*i*j*j<=max; j+=2) seive[i * j] = false;
    }
    for (long long i=2; i*i<=max; i++) {
        if (seive[i]) primes.push_back(i);
    }
    // if x = a * i^2 for integer a, i, then i <= sqrt(x).
    // Use seive on [min, max], marking multiples of i^2 where i is a prime number satisfying i <= sqrt(x).
    for (long long i: primes) {
        // x is multiple of (i * i) nearest to min.
        long long x;
        if (min % (i * i) == 0) x = min;
        else x = min - (min % (i * i)) + (i * i);
        for (long long j=x; j<=max; j+=i*i) filter[j - min] = true;
    }
    long long answer {0};
    for (long long i=min; i<=max; i++) answer += (filter[i - min] == false);
    // Output
    std::cout << answer << std::endl;
    return 0;
}