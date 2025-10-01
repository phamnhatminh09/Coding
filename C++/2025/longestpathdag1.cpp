#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<int, ii> iii;

vector<int> par;

int find(int u) {
    if (par[u] != u) par[u] = find(par[u]);
    
    return par[u];
}

bool dsu(int u, int v) {
    u = find(u);
    v = find(v);
    if (u == v) return false;
    par[v] = u;
    return true;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

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

    for (ll num : res) cout << num << '\n';

    return 0;
}