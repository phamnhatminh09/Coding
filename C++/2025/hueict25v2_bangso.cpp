#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const ll mod = 1e9 + 7;

void Solve() {
	long n;
	cin >> n;
    n %= mod;
    cout << (2 * n % mod) * (n % mod) % mod * (n % mod) % mod;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}