#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const ll oo = LLONG_MAX;

vector<int> pre(N + 1, -1);
vector<ll> d(N + 1, oo);

void dijkstra(int n, const vector<vector<ii>>& adj, int source) {
	priority_queue<li, vector<li>, greater<li>> pq;
	d[source] = 0;
	pq.push({0, source});
	
	while (!pq.empty()) {
		ll du = pq.top().first, u = pq.top().second;
		pq.pop();
		
		if (du > d[u]) continue;
		
		for (auto& node : adj[u]) {
			int v = node.first, w = node.second;
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				pre[v] = u;
				pq.push({d[v], v});
			}
		}
	}
}

void Solve() {
	int n, m, s, t;
	cin >> n >> m >> s >> t;
	
	vector<vector<ii>> adj(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		adj[u].emplace_back(v, c);
		adj[v].emplace_back(u, c);
	}
	
	dijkstra(n, adj, s);
	
	if (d[t] == oo) {
		cout << -1;
		return;
	}
	
	cout << d[t] << '\n';
	
	vector<int> path;
	for (int v = t; v != -1; v = pre[v]) path.push_back(v);
	
	reverse(path.begin(), path.end());
	
	for (auto x : path) cout << x << ' ';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}