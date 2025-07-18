#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int t;
	cin >> t;
	
	while (t--) {
		int n, q;
		cin >> n >> q;
		
		vector<int> a(n + 1);
		for (int i = 1; i <= n; ++i) cin >> a[i];
		
		vector<vector<pair<int, int>>> adj(n + 1);
		ll res = 0;
		for (int i = 0; i < n - 1; ++i) {
			int u, v, c;
			cin >> u >> v >> c;
			adj[u].emplace_back(v, c);
			adj[v].emplace_back(u, c);
			if (a[u] != a[v]) res += c;
		}
		
		while (q--) {
			int vert, x;
			cin >> vert >> x;
			int temp = a[vert];
			
			if (temp == x) {
				cout << res << '\n';
				continue;
			}
			
			for (auto &edge : adj[vert]) {
				int curr = edge.first, cost = edge.second;
				if (a[curr] == temp) res += cost;
				else if (a[curr] == x) res -= cost;
			}
			
			a[vert] = x;
			cout << res << '\n';
		}
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}