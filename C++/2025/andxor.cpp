#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<int> a(N);

void update(int l, int r, int x, int t) {
	if (t == 2) {
		for (int i = l; i <= r; ++i) a[i] = a[i] & x;
	}
	if (t == 3) {
		for (int i = l; i <= r; ++i) a[i] = a[i] ^ x;
	}
}

void Solve() {
	int n, q;
	cin >> n;
	
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	cin >> q;
	
	while (q--) {
		int t, l, r, x = 0;
		cin >> t;
		if (t == 1) {
			cin >> l >> r;
			int res = 0;
			for (int i = l; i <= r; ++i) res += a[i];
			cout << res << '\n';
			
		}
		else if (t == 2) {
			cin >> l >> r >> x;
			update(l, r, x, t);
		}
		else if (t == 3) {
			cin >> l >> r >> x;
			update(l, r, x, t);
		}
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}