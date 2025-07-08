#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(int x) {
	int k = sqrt(x);
	return (k * k == x);
}

void Solve() {
	unordered_map<long, long> cnt;
	long n, q;
	cin >> n;
	
	ll a[n];
	for (int i = 0; i < n; ++i) {
		cin >> a[i];
		cnt[a[i]]++;
	}
	
	cin >> q;
	
	while(q--) {
		ll b, c, res = 0;
		cin >> b >> c;
		
		if (b * b - 4 * c < 0) {
			cout << 0 << "\n";
			continue;
		}
		int d = b * b - 4 * c;
		if (check(d)) {
			if ((b + (int) sqrt(d)) % 2 == 0) {
				int ai = (b + (int) sqrt(d)) / 2;
				int aj = b - ai;
				if (ai != aj) res += cnt[ai] * cnt[aj];
				else res += (cnt[ai] * cnt[aj] - 1) / 2;
			}
		}
		cout << res << "\n";
	}
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}