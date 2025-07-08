#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const int MAX = 1e5 + 5;
const int LOG = 20;

vector<int> adj[MAX];
int d[MAX];
int par[MAX][LOG];

void dfs(int u, int p) {
    par[u][0] = p;
    d[u] = d[p] + 1;
    for (int v : adj[u]) {
        if (v != p) dfs(v, u);
    }
}

void preprocess(int n) {
    dfs(1, 0);
    for (int j = 1; j < LOG; ++j) {
        for (int i = 1; i <= n; ++i) par[i][j] = par[par[i][j - 1]][j - 1];
    }
}

int lca(int u, int v) {
    if (d[u] < d[v]) swap(u, v);
    for (int j = LOG - 1; j >= 0; --j) {
        if (d[u] - (1 << j) >= d[v]) {
            u = par[u][j];
        }
    }
    
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; --j) {
        if (par[u][j] != par[v][j]) {
            u = par[u][j];
            v = par[v][j];
        }
    }
    
    return par[u][0];
}

int findNodeOnPath(int a, int b, int c) {
    int bc = lca(b, c);
    int ab = lca(a, b);
    int ac = lca(a, c);

    if (d[ab] > d[bc]) return ab;
    else if (d[ac] > d[bc]) return ac;
    else return bc;
}

void Solve() {
	int n, m;
    cin >> n >> m;

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    preprocess(n);

    while (m--) {
        int a, b, c;
        cin >> a >> b >> c;
        cout << findNodeOnPath(a, b, c) << '\n';
    }

}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}