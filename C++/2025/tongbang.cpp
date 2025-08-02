#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int long long

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const int mod = 1532023;

ll mmod(ll x) {
	return (x % mod + mod) % mod;
}

void Solve() {
	int m, n;
	cin >> m >> n;
	
	if (n % 2 != 0) {
		if (m % 2 != 0) cout << mmod((mmod(m) * mmod(n) + 1) * (mmod(m) * mmod(n) + 1)) / 4;
		else cout << mmod((mmod(m) * mmod(n)) * (mmod(m) * mmod(n))) / 4;
	}
	else {
		ll j = 0, sum = 0;
		vector<int> firstrow(n / 2);
		for (int i = 1; i <= n; i += 2) {
			firstrow[j] = i;
			j++;
		}
		
		ll even = m / 2, odd;
		if (m % 2 == 0) odd = m / 2;
		else odd = m / 2 + 1;
		
		for (int x : firstrow) sum += x;
		sum = mmod(sum);
		
		ll even_interval = mmod(mmod(n) / 2 * (mmod(n) + 1)), odd_interval = mmod(mmod(n) / 2 * (mmod(n) - 1));
		if (m != n) sum = mmod(mmod(sum) * mmod(m)) + mmod(mmod(even_interval) * mmod(odd) * mmod(mmod(m) / 2)) + mmod(mmod(odd_interval) * mmod(even) * mmod(mmod(m) / 2));
		else sum = mmod(mmod(sum) * mmod(m)) + mmod(mmod(even_interval) * mmod(odd) * mmod(mmod(m) / 2)) + mmod(mmod(odd_interval) * mmod(even) * mmod(mmod(m) / 2 - 1));
		
		cout << mmod(sum);
	}
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}