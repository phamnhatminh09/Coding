#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;
typedef pair<int, ii> iii;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

vector<int> par;

int find(int u) {
	if (par[u] != u) par[u] = find(par[u]);
	
	return par[u];
}

bool dsu(int u, int v) {
	u = find(u), v = find(v);
	
	if (u == v) return false;
	par[v] = u;
	return true;
}

void Solve() {
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<iii> adj(m);
	for (int i = 0; i < m; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		adj[i] = {w, {u, v}};
	}
	
	sort(adj.begin(), adj.end(), greater<iii>());
	
	par.resize(n + 1);
	
	vector<bool> visited(m, false);
	vector<ll> res(k, 0);
	
	for (int i = 0; i < k; ++i) {
		for (int j = 1; j <= n; ++j) par[j] = j;
		
		ll sum = 0;
		for (int j = 0; j < m; ++j) {
			if (!visited[j]) {
				int u = adj[j].second.first, v = adj[j].second.second;
				
				if (dsu(u, v)) {
					sum += adj[j].first;
					visited[j] = true;
				}
			}
		}
		
		res[i] = sum;
	}
	
	for (auto x : res) cout << x << '\n';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}