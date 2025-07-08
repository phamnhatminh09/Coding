#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll maxH(ll h[5]) {
	ll b = 0;
	for (ll i = 0; i < 5; ++i) {
		ll mn = h[i];
		for (ll j = i; j < 5; ++j) {
			mn = min(mn, h[j]);
			b = max(b , mn * (j - i + 1));
		}
	}
	
	return b;
}

ull cnt(ll t, const array<ll, 10> &M) {
	const ll st = 161051;
	static vector<ull> dp0, dp1;
	dp0.assign(st, 0);
	dp1.assign(st, 0);
	
	dp0[0] = 1;
	ll W[5] = {1, 11, 121, 1331, 14641};
	
	for (ll c = 0; c < 10; ++c) {
		fill(dp1.begin(), dp1.end(), 0);
		ll m = M[c];
		
		for (ll s = 0; s < st; ++ s) {
			ull v = dp0[s];
			if (!v) continue;
			
			ll h[5], x = s;
			for (ll r = 0; r < 5; ++r) {
				h[r] = x % 11;
				x /= 11;
			}
			
			for (ll sub = m; ; sub = (sub - 1) & m) {
				ll h2[5];
				
				for (ll r = 0; r < 5; ++r) h2[r] = (sub >> r & 1) ? h[r] + 1 : 0;
				
				if (maxH(h2) <= t) {
					ll s2 = 0;
					for (ll r = 0; r < 5; ++r) s2 += h2[r] * W[r];
					dp1[s2] += v;
				}
				
				if (sub == 0) break;
			}
		}
		dp0.swap(dp1);
	}
	
	ull sum = 0;
	for (auto v : dp0) sum += v;
	return sum;
}

void Solve() {
	ll s;
	cin >> s;
	array<ll, 10> m{};
	
	string r;
	for (ll i = 0; i < 5; ++i) {
		cin >> r;
		for (ll j = 0; j < 10; ++j) {
			if (r[j] == '0') m[j] |= 1 << i;
		}
	}
	
	ull a = cnt(s, m), b = s > 0 ? cnt(s - 1, m) : 0;
	cout << a - b;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}