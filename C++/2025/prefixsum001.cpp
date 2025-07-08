#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m;
	cin >> n >> m;
	
	vector<int> v(n);
	for (int &x : v) cin >> x;
	
	sort(v.begin(), v.end());
	
	vector<ll> prefix(n + 1, 0);
	for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + v[i];
	
	while (m--) {
		int k;
		cin >> k;
		
		ll pos = lower_bound(v.begin(), v.end(), k) - v.begin(), cost = (1LL * k * pos - prefix[pos]) + ((prefix[n] - prefix[pos]) - 1LL * k * (n - pos));
		cout << cost << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}