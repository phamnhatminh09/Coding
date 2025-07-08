#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m, b, r;
	cin >> n >> m >> b >> r;
	
	vector<int> wh(b), camp(r);
	for (int i = 0; i < b; ++i) cin >> wh[i];
	for (int i = 0; i < r; ++i) cin >> camp[i];
	
	vector<vector<int>> g(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	vector<int> dist(n + 1, INT_MAX);
	queue<int> q;
	
	for (int x : wh) {
		dist[x] = 0;
		q.push(x);
	}
	
	while (!q.empty()) {
		int curr = q.front();
		q.pop();
		
		for (int x : g[curr]) {
			if (dist[x] == INT_MAX) {
				dist[x] = dist[curr] + 1;
				q.push(x);
			}
		}
	}
	
	for (int i = 0; i < r; ++i) cout << dist[camp[i]] << ' ';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}