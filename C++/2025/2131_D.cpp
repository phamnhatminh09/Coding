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

void Solve() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		
		vector<vector<int>> adj(n + 1);
		vector<int> deg(n + 1, 0);
		
		for (int i = 0; i < n - 1; ++i) {
			int u, v;
			cin >> u >> v;
			adj[u].emplace_back(v);
			adj[v].emplace_back(u);
			deg[u]++;
			deg[v]++;
		}
		
		if (n == 2) {
			cout << 0 << '\n';
			continue;
		}
		
		int leaf = 0;
		for (int i = 1; i <= n; ++i) {
			if (deg[i] == 1) leaf++;
		}
		
		int maxx = 0;
		for (int u = 1; u <= n; ++u) {
			int cnt = 0;
			
			for (auto node : adj[u]) {
				if (deg[node] == 1) cnt++;
			}
			
			int i = (deg[u] == 1) ? 1 : 0;
			maxx = max(maxx, cnt + i);
		}
		
		cout << leaf - maxx << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}