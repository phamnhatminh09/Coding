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
	
	unordered_map<int, vector<int>> adj;
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	vector<bool> visited(n + 1, false);
	vector<pair<int, int>> edge;
	
	for (int i = 1; i <= n; ++i) {
		if (!visited[i]) {
			queue<int> q;
			q.push(i);
			visited[i] = true;
			
			while (!q.empty()) {
				int u = q.front();
				q.pop();
				
				for (int v : adj[u]) {
					if (!visited[v]) {
						visited[v] = true;
						edge.emplace_back(u, v);
						q.push(v);
					}
				}
			}
		}
	}
	
	cout << edge.size() << '\n';
	for (auto [u, v] : edge) cout << u << ' ' << v << '\n';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}