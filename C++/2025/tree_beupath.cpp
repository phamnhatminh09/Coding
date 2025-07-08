#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll n = 1e5 + 5;
vector<vector<ll>> adj;
vector<ll> type, par, depth;
vector<bool> check;

void dfs(ll u, ll p) {
    par[u] = p;
    for (ll v : adj[u]) {
        if (v != p) {
            depth[v] = depth[u] + 1;
            dfs(v, u);
        }
    }
}

void path(ll u, ll v) {
    while (u != v) {
        if (depth[u] > depth[v]) {
            check[u] = true;
            u = par[u];
        }
        else {
            check[v] = true;
            v = par[v];
        }
    }
    check[u] = true;
}

void Solve() {
	ll n;
    cin >> n;

    type.resize(n + 1);
    for (ll i = 1; i <= n; ++i) cin >> type[i];

    adj.resize(n + 1);
    for (ll i = 0; i < n - 1; ++i) {
        ll u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    par.resize(n + 1);
    depth.resize(n + 1);
    dfs(1, -1);

    vector<ll> t1, t2;
    for (ll i = 1; i <= n; ++i) {
        if (type[i] == 1) t1.push_back(i);
        if (type[i] == 2) t2.push_back(i);
    }

    check.assign(n + 1, false);
    for (ll u : t1) {
        for (ll v : t2) path(u, v);
    }

    ll x = n - 1, y = 0;
    for (ll u = 1; u <= n; ++u) {
        if (check[u] && par[u] != -1) y++;
    }
    
    cout << x - y;
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}