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

struct edge {
	int u, v, c;
	bool operator < (const edge& other) const {
		return c < other.c;
	}
};

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
	int n, m;
	cin >> n >> m;
	
	vector<edge> adj(m);
	for (int i = 0; i < m; ++i) cin >> adj[i].u >> adj[i].v >> adj[i].c;
	
	sort(adj.begin(), adj.end());
	
	for (int i = 1; i <= n; ++i) {
		par[i] = i;
		r[i] = 0;
	}
	
	ll res = 0, used = 0;
	
	for (int i = 0; i < m; ++i) {
		if (used == n - 1) break;
		
		if (find(adj[i].u) != find(adj[i].v)) {
			dsu(adj[i].u, adj[i].v);
			res += adj[i].c;
			used++;
		}
	}
	
	cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}