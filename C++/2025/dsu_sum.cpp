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

int par[N], sum[N];

int find(int u) {
	if (par[u] != u) par[u] = find(par[u]);
	
	return par[u];
}

void dsu(int a, int b) {
	int u = find(a), v = find(b);
	
	if (u != v) {
		if (sum[u] < sum[v]) swap(u, v);
		par[v] = u;
		sum[u] += sum[v];
	}
}

void Solve() {
	int n, q;
	cin >> n >> q;
	
	for (int i = 1; i <= n; ++i) par[i] = sum[i] = i;
	
	while (q--) {
		int t, u, v;
		cin >> t;
		
		if (t == 1) {
			cin >> u >> v;
			dsu(u, v);
		}
		else {
			cin >> u;
			cout << sum[find(u)] << '\n';
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
