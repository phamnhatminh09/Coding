#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

pair<int, int> bfs(int start, vector<vector<int>>& adj, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    
    q.push(start);
    dist[start] = 0;
    int temp = start, maxx = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                
                if (dist[v] > maxx) {
                    maxx = dist[v];
                    temp = v;
                }
            }
        }
    }
    
    return {temp, maxx};
}

void Solve() {
	int n;
    cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    pair<int, int> bfs1 = bfs(1, adj, n);
    int temp = bfs1.first;
    
    pair<int, int> bfs2 = bfs(temp, adj, n);
    int res = bfs2.second;

    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}