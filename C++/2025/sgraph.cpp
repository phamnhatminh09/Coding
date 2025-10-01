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

void dijkstra(int n, const vector<vector<ii>>& adj, vector<ll>& d, int source) {
	d.assign(n + 1, oo);
	priority_queue<li, vector<li>, greater<li>> pq;
	d[source] = 0;
	pq.push({0, source});
	
	while (!pq.empty()) {
		int du = pq.top().first, u = pq.top().second;
		pq.pop();
		
		if (du > d[u]) continue;
		
		for (auto node : adj[u]) {
			int v = node.first, w = node.second;
			
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				pq.push({d[v], v});
			}
		}
	}
}

void Solve() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<ii>> adj(n + 1), rev(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[u].emplace_back(v, w);
		rev[v].emplace_back(u, w);
	}
	
	vector<ll> d1, d2;
	dijkstra(n, adj, d1, 1);
	dijkstra(n, rev, d2, 1);
	
	for (int i = 2; i <= n; ++i) {
		if (d1[i] == oo || d2[i] == oo) cout << "-1\n";
		else cout << d1[i] + d2[i] << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}