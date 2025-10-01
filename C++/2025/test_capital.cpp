#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<int>> adj;
vector<int> parent, depth;
vector<ll> w, sum_w, sum_dw;
int n, q;

void dfs(int u, int p) {
    parent[u] = p;
    for (int v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

void prep() {
    parent.resize(n + 1);
    depth.resize(n + 1);
    dfs(1, -1);
}

void update1(int u, int c) {
    w[u] += c;
}

void update2(int u, int c) {
    queue<int> q;
    q.push(u);
    
    while (!q.empty()) {
        int v = q.front();
        q.pop();
        w[v] += c;
        
        for (int x : adj[v]) {
            if (x != parent[v]) q.push(x);
        }
    }
}

ll cal(int u) {
    ll cost = 0;
    queue<pair<int, int>> q;
    q.push({u, 0});
    
    vector<bool> visited(n + 1, false);
    visited[u] = true;
    
    while (!q.empty()) {
        auto [v, dist] = q.front();
        q.pop();
        cost += w[v] * dist;
        
        for (int x : adj[v]) {
            if (!visited[x]) {
                visited[x] = true;
                q.push({x, dist + 1});
            }
        }
    }
    
    return cost;
}

int find() {
    ll minn = 1e18, temp = 1;
    
    for (int u = 1; u <= n; ++u) {
        ll cost = cal(u);
        if (cost < minn || (cost == minn && u < temp)) {
            minn = cost;
            temp = u;
        }
    }
    
    return temp;
}

void Solve() {
	cin >> n >> q;
	
    adj.resize(n + 1);
    w.resize(n + 1);
    
    for (int i = 1; i <= n; ++i) cin >> w[i];
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    prep();

    while (q--) {
        int t, u, c;
        cin >> t >> u >> c;
        
        if (t == 1) update1(u, c);
        else update2(u, c);
        
        cout << find() << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}