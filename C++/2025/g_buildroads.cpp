#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<int>> adj;
vector<bool> visited;

void bfs(int start) {
    queue<int> q;
    q.push(start);
    
    visited[start] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
}

void Solve() {
    int n, m;
    cin >> n >> m;
    adj.resize(n + 1);
    visited.assign(n + 1, false);

    for (int i = 0; i < m; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    vector<int> v;
    for (int i = 1; i <= n; ++i) {
        if (!visited[i]) {
            bfs(i);
            v.push_back(i);
        }
    }

    int k = v.size();
    cout << k - 1 << '\n';
    for (int i = 1; i < k; ++i) cout << v[i - 1] << ' ' << v[i] << '\n';
}

int main() {
    faster
    
    Solve();
    
    return 0;
}
