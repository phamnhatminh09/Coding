#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<int>> tree;
vector<int> a, b;
ll res = 0;

void dfs(int u, int par, vector<pair<int, int>>& vp) {
    for (auto& v : vp) {
        int au = v.first, bu = v.second, ma = max(au, a[u]), mb = max(bu, b[u]);
        res += min(ma, mb);
    }
    
    vp.push_back({a[u], b[u]});
    for (int v : tree[u]) {
        if (v != par) dfs(v, u, vp);
    }
    
    vp.pop_back();
}


void Solve() {
    int n;
    cin >> n;
    a.resize(n + 1);
    b.resize(n + 1);
    tree.resize(n + 1);

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }

    vector<pair<int, int>> vp;
    dfs(1, -1, vp);

    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}