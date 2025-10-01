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
	int n, m;
	cin >> n >> m;
	
	vector<set<int>> adj(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].insert(v);
		adj[v].insert(u);
	}
	
	int minn = 1;
	for (int i = 2; i <= n; ++i) {
		if (adj[i].size() < adj[minn].size()) minn = i;
	}
	
	set<int> unvisited;
	for (int i = 1; i <= n; ++i) unvisited.insert(i);
	
	int res = 0;
	queue<int> q;
	
	unvisited.erase(minn);
	q.push(minn);
	
	while (!unvisited.empty() || !q.empty()) {
		if (q.empty()) {
			res++;
			int node = *unvisited.begin();
			unvisited.erase(node);
			q.push(node);
		}
		
		int u = q.front();
		q.pop();
		
		vector<int> rem;
		for (auto v : unvisited) {
			if (adj[u].find(v) == adj[u].end()) {
				rem.emplace_back(v);
				q.push(v);
			}
		}
		
		for (auto x : rem) unvisited.erase(x);
	}
	
	cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}