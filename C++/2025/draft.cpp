#include <iostream>
#include <climits>

using namespace std;

int main() {
    long long N;
    cin >> N;

    long long min_operations = LLONG_MAX;

    for (long long fives = 0; fives <= N / 5; ++fives) {
        long long remaining = N - 5 * fives;
        for (long long threes = 0; threes <= remaining / 3; ++threes) {
            long long remaining_after_3 = remaining - 3 * threes;
            if (remaining_after_3 % 2 == 0) {
                long long twos = remaining_after_3 / 2;
                long long total_operations = fives + threes + twos;
                if (total_operations < min_operations) {
                    min_operations = total_operations;
                }
            }
        }
    }

    cout << min_operations << endl;

    return 0;
}