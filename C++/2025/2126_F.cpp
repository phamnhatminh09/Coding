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

struct edge {
	int u, v, c;
};

void Solve() {
	int t;
	cin >> t;
	
	while (t--) {
		int n, q;
		cin >> n >> q;
		
		vector<int> color(n + 1);
		for (int i = 1; i <= n; ++i) cin >> color[i];
		
		vector<edge> e(n - 1);
		vector<vector<ii>> adj(n + 1);
		for (int i = 0; i < n - 1; ++i) {
			int u, v, c;
			cin >> u >> v >> c;
			
			e[i] = {u, v, c};
			adj[u].emplace_back(v, c);
			adj[v].emplace_back(u, c);
		}
		
		vector<int> par(n + 1, -1), etp(n + 1, 0);
		queue<int> qu;
		qu.push(1);
		par[1] = 0;
		
		while (!qu.empty()) {
			int u = qu.front();
			qu.pop();
			
			for (const auto& node : adj[u]) {
				int v = node.first, c = node.second;
				if (par[v] == -1 && v != par[u]) {
					par[v] = u;
					etp[v] = c;
					qu.push(v);
				}
			}
		}
		
		ll res = 0;
		for (const auto& x : e) {
			if (color[x.u] != color[x.v]) res += x.c;
		}
		
		while (q--) {
			int v, x;
			cin >> v >> x;
			
			if (color[v] == x) {
				cout << res << '\n';
				continue;
			}
			
			if (par[v] != 0) {
				int u = par[v], c = etp[v];
				if (color[u] == color[v]) res += c;
				else if (color[u] == x) res -= c;
			}
			
			color[v] = x;
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