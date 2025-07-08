#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll n = 1e5 + 5;

void bfs(int start, vector<vector<int>>& adj, vector<int>& dist) {
    queue<int> q;
    q.push(start);
    dist[start] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == INT_MAX) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
}

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
    
    int x, y;
    cin >> x >> y;
    
    vector<int> distX(n + 1, INT_MAX), distY(n + 1, INT_MAX);
    
    bfs(x, adj, distX);
    bfs(y, adj, distY);
    
    int q;
    cin >> q;
    
    while (q--) {
        int z;
        cin >> z;
        
        if (distX[z] <= distY[z]) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}