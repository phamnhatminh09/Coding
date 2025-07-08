#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m, k, b;
    cin >> n >> m >> k;
    
    vector<vector<int>> g(n + 1);
    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<int> a(k);
    for (int i = 0; i < k; ++i) cin >> a[i];
    
    cin >> b;

    vector<int> dist(n + 1, -1);
    queue<int> q;
    dist[b] = 0;
    q.push(b);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : g[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < k; ++i) cout << dist[a[i]] << ' ';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}