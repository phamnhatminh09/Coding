#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
vector<vector<int>> adj;
vector<int> a;
int m, res = 0;

void dfs(int u, int p, int c) {
	if (a[u] == 1) c++;
	else c = 0;
	
	if (c > m) return;
	
	bool check = true;
	for (int v : adj[u]) {
		if (v != p) {
			check = false;
			dfs(v, u, c);
		}
	}
	
	if (check) res++;
}

void Solve() {
	int n;
	cin >> n >> m;
	
	a.resize(n + 1);
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	adj.resize(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    dfs(1, - 1, 0);
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}