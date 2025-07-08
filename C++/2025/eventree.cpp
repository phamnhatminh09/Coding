#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<int>> adj;
vector<int> sub;
int res = 0;

void dfs(int u, int p) {
	sub[u] = 1;
	
	for (int v : adj[u]) {
		if (v != p) {
			dfs(v, u);
			sub[u] += sub[v];
		}
	}
	
	if (sub[u] % 2 == 0 && u != 1) res++;
}

void Solve() {
	int n;
	cin >> n;
	
	if (n % 2 != 0) {
		cout << -1;
		return;
	}
	
	adj.resize(n + 1);
	sub.resize(n + 1);
	
	for (int i = 0; i < n - 1; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfs(1, -1);
	cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}