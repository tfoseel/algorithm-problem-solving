# BOJ 14853. 동전 던지기

import sys


def solve():
    # Input
    v = sys.stdin.readline()
    v = list(map(int, v.split()))
    n1, m1, n2, m2 = v[0], v[1], v[2], v[3]
    # p and q follow uniform distribution, so it can be thought as picking one real number from [0, 1].
    # A toss of coin P (or Q) can be thought as picking one real number x from [0, 1],
    # considering the result 'head' if x > p (or q) and 'tail' otherwise.
    # Therefore, the problem can be reduced into picking (n1 + 1) points about coin P
    # among (n1 + n2 + 2) points, which are on number line [0, 1].
    # When (n1 + 1) points are chosen, left m1 points indicate head of coin P toss,
    # next one point indicates value of p, and last (n1 - m1) points indicate tail of coin P toss.
    # Remaining (n2 + 1) points can be labeled with the same rule about coin Q.
    # Consider point x = p on the line.
    # There can be m1 points at minimum and (m1 + m2) points at maximum, on the left.
    # If there are k(m1 <= k <= m1 + m2) points on the left,
    # we can choose m1 points among them and (n1 - m1) points among (n1 + n2 + 1 - k) points on the right about coin P.
    # Then, we can determine q uniquely, by finding (m2 + 1)-th point among remaining points from the left.
    # Here, p < q always holds.
    # To compute these values takes a lot of time, so first try to compute when k = m1 and reuse the value for other k.
    base = 1
    for i in range(0, n2 + 1):
        base = base * (n1 - m1 + 1 + i) / (n1 + 2 + i)
    answer = base
    # Here, when k = m1 + i, the desired value is base * (m1 + i) * (n2 + 2 - i) / i / (n1 + n2 - m1 + 2 - i).
    for i in range(1, m2 + 1):
        base *= (m1 + i) * (n2 + 2 - i) / i / (n1 + n2 - m1 + 2 - i)
        answer += base
    # Output
    sys.stdout.write(str(answer) + '\n')


n = int(input())
for i in range(n):
    solve()
