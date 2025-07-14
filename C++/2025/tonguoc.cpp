#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<long long> prep(long long n) {
    vector<long long> div;
    
    for (long long i = 1; i <= sqrt(n); ++i) {
        if (n % i == 0) {
            div.push_back(i);
            if (i != n / i) div.push_back(n / i);
        }
    }
    
    return div;
}

void Solve() {
	long long a, b;
    cin >> a >> b;

    vector<long long> div = prep(a);
    long long sum = 0;

    for (long long x : div) {
        if (b % (3 * x) == 0) sum += x;
    }

    cout << sum;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}