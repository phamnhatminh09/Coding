#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}

/*#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
const int MAXN = 1e5 + 5;
const int LOG = 20;

vector<int> adj[MAXN];
int parent[MAXN][LOG], depth[MAXN];
int a[MAXN];
int n, k, q;

void dfs(int u, int p) {
    parent[u][0] = p;
    depth[u] = depth[p] + 1;
    for (int v : adj[u]) {
        if (v != p) {
            dfs(v, u);
        }
    }
}

void preprocess() {
    dfs(1, 0);
    for (int j = 1; j < LOG; ++j) {
        for (int i = 1; i <= n; ++i) {
            parent[i][j] = parent[parent[i][j - 1]][j - 1];
        }
    }
}

int lca(int u, int v) {
    if (depth[u] < depth[v]) swap(u, v);
    for (int j = LOG - 1; j >= 0; --j) {
        if (depth[u] - (1 << j) >= depth[v]) {
            u = parent[u][j];
        }
    }
    if (u == v) return u;
    for (int j = LOG - 1; j >= 0; --j) {
        if (parent[u][j] != parent[v][j]) {
            u = parent[u][j];
            v = parent[v][j];
        }
    }
    return parent[u][0];
}

vector<int> get_path(int u, int v) {
    int ancestor = lca(u, v);
    vector<int> path;
    while (u != ancestor) {
        path.push_back(u);
        u = parent[u][0];
    }
    path.push_back(ancestor);
    vector<int> temp;
    while (v != ancestor) {
        temp.push_back(v);
        v = parent[v][0];
    }
    reverse(temp.begin(), temp.end());
    for (int x : temp) {
        path.push_back(x);
    }
    return path;
}

bool is_super_happy(ll x, int k) {
    if (x == 0) return false;
    ll y = round(pow(x, 1.0 / k));
    while (pow(y, k) < x) y++;
    while (pow(y, k) > x) y--;
    return pow(y, k) == x;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k >> q;
    for (int i = 1; i <= n; ++i) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    preprocess();

    while (q--) {
        int u, v;
        cin >> u >> v;
        vector<int> path = get_path(u, v);
        int m = path.size();
        int res = 0;
        for (int i = 0; i < m; ++i) {
            for (int j = i + 1; j < m; ++j) {
                ll product = (ll)a[path[i]] * a[path[j]];
                if (is_super_happy(product, k)) {
                    res++;
                }
            }
        }
        cout << res << '\n';
    }

    return 0;
}*/