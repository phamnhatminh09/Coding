#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<int> adj[N];
int dist[N];

pair<int, int> bfs(int x, int n) {
	fill(dist, dist + n + 1, -1);
	queue<int> q;
	
	dist[x] = 0;
	q.push(x);
	int temp = x;
	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		
		for (int v : adj[u]) {
			if (dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q.push(v);
				
				if (dist[v] > dist[temp]) temp = v;
			}
		}
	}
	
	return {temp, dist[temp]};
}

void Solve() {
	int n;
	cin >> n;
	
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	cout << bfs(bfs(1, n).first, n).second;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}