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

vector<ll> dijkstra(int n, const vector<vector<ii>>& adj, int source) {
	vector<ll> d(n + 1, oo);
	d[source] = 0;
	priority_queue<li, vector<li>, greater<li>> pq;
	pq.push({0, source});
	
	while (!pq.empty()) {
		ll du = pq.top().first, u = pq.top().second;
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
	
	return d;
}

void Solve() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<ii>> adj(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].emplace_back(b, c);
	}
	
	vector<ll> d = dijkstra(n, adj, 1);
	
	for (int i = 1; i <= n; ++i) cout << d[i] << ' ';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}