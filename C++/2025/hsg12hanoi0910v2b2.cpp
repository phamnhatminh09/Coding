#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;
typedef pair<ii, int> iii;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const int oo = 1e9;

int n, m;

void dijkstra (int source, const vector<vector<ii>>& adj, vector<int>& d) {
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	pq.push({0, source});
	d[source] = 0;
	
	while (!pq.empty()) {
		int du = pq.top().first, u = pq.top().second;
		pq.pop();
		
		if (du > d[u]) continue;
		
		for (auto& node : adj[u]) {
			int v = node.first, w = node.second;
			
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				pq.push({d[v], v});
			}
		}
	}
}

void Solve() {
	cin >> n >> m;
	
	vector<vector<ii>> adj(n + 1), rev(n + 1);
	vector<ii> edge;
	
	for (int i = 0; i < m; ++i) {
		int u, v, c;
		cin >> u >> v >> c;
		adj[u].emplace_back(v, c);
		adj[v].emplace_back(u, c);
		rev[u].emplace_back(v, c);
		rev[v].emplace_back(u, c);
		edge.emplace_back(u, v);
	}
	
	vector<int> d1(n + 1, oo), d2(n + 1, oo);
	dijkstra(1, adj, d1);
	dijkstra(n, rev, d2);
	
	int minn = d1[n];
	
	for (auto& x : edge) {
		int u = x.first, v = x.second;
		
		if (d1[u] != oo && d2[v] != oo) minn = min(minn, d1[u] + d2[v]);
		if (d1[v] != oo && d2[u] != oo) minn = min(minn, d1[v] + d2[u]);
	}
	
	cout << minn;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}