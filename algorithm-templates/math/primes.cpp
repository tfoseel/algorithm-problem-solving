#include <iostream>
#include <vector>

// Return a vector of prime numbers lower or equal to n.
// If seive is declared outside, it can be used to determine if given number is prime in O(1) time.
std::vector<int> get_primes(int n) {
    std::vector<int> primes;
    std::vector<bool> seive (n + 1, false);
	seive[0] = true;
	seive[1] = true; 
	for (int i=2; i<=n; i++) {
		if (seive[i]) continue;
		primes.push_back(i);
		for (int j=i*2; j<=n; j+=i) seive[j] = true;
	}
    return primes;
}