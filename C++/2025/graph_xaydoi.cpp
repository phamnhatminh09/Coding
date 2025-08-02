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
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	vector<int> color(n + 1, -1);
	bool check = true;
	
	for (int i = 1; i <= n; ++i) {
		if (color[i] == -1) {
			queue<int> q;
			q.push(i);
			color[i] = 0;
			
			while (!q.empty() && check) {
				int u = q.front();
				q.pop();
				
				for (int v : adj[u]) {
					if (color[v] == -1) {
						color[v] = color[u] ^ 1;
						q.push(v);
					}
					else if (color[v] == color[u]) {
						check = false;
						break;
					}
				}
			}
		}
	}
	
	if (!check) cout << "IMPOSSIBLE";
	else {
		for (int i = 1; i <= n; ++i) cout << color[i] << ' ';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}