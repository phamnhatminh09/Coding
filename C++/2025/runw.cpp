#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<int> bfs(const vector<vector<int>>& adj, int x) {
	int n = adj.size();
	vector<int> dist(n, -1);
	queue<int> q;
	
	q.push(x);
	dist[x] = 0;
	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		
		for (int v : adj[u]) {
			if (dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	
	return dist;
}

void Solve() {
	int n, k;
	cin >> n >> k;
	
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	vector<int> dist = bfs(adj, 1);
	sort(dist.begin() + 1, dist.end(), greater<int>());
	
	ll res = 0;
	for (int i = 1; i <= k && i <= n; ++i) res += dist[i];
	cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}