#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> adj(n + 1);
	for (int i = 0; i < m; ++i) {
		int a, b;
		cin >> a >> b;
		adj[a].push_back(b);
		adj[b].push_back(a);
	}
	
	vector<int> dist(n + 1, -1), parent(n + 1, -1);
	queue<int> q;
	q.push(1);
	dist[1] = 1;
	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		for (int v : adj[u]) {
			if (dist[v] == -1) {
				dist[v] = dist[u] + 1;
				parent[v] = u;
				q.push(v);
			}
		}
	}
	
	if (dist[n] == -1) cout << "IMPOSSIBLE";
	else {
		vector<int> path;
		for (int v = n; v != -1; v = parent[v]) path.push_back(v);
		
		reverse(path.begin(), path.end());
		cout << dist[n] << '\n';
		
		for (int v : path) cout << v << ' ';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}