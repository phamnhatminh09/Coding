#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
vector<vector<pair<ll, ll>>> adj;
vector<ll> edge;
vector<ll> sub;

void dfs(ll u, ll p) {
	sub[u] = 1;
	
	for (auto &x : adj[u]) {
		ll v = x.first, t = x.second;
		if (v != p) {
			dfs(v, u);
			sub[u] += sub[v];
			edge[t] = sub[v] * (sub[0] - sub[v]);
		}
	}
}


void Solve() {
	ll n;
	cin >> n;
	
	adj.resize(n + 1);
	edge.resize(n - 1);
	sub.resize(n + 1);
	
	for (ll i = 0; i < n - 1; ++i) {
		ll u, v;
		cin >> u >> v;
		adj[u].emplace_back(v, i);
		adj[v].emplace_back(u, i);
	}
	
	sub[0] = n;
	dfs(1, -1);
	
	for (ll i = 0; i < n - 1; ++i) cout << edge[i] << '\n';
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}