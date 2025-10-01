#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const ll oo = 1e18;

int par[N], r[N];

int find(int u) {
	if (par[u] != u) par[u] = find(par[u]);
	
	return par[u];
}

void dsu(int a, int b) {
	int u = find(a), v = find(b);
	
	if (u != v) {
		if (r[u] > r[v]) par[v] = u;
		else if (r[u] < r[v]) par[u] = v;
		else {
			par[v] = u;
			r[u]++;
		}
	}
}

void Solve() {
	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; ++i) {
		par[i] = i;
		r[i] = 0;
	}
	
	while (q--) {
		int t, u, v;
		cin >> t >> u >> v;
		
		if (t == 1) dsu(u, v);
		else {
			if (find(u) == find(v)) cout << "YES\n";
			else cout << "NO\n";
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
