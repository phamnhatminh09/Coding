#include <bits/stdc++.h>
using namespace std;

#define int long long
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<ii> vii;

#define pb push_back
#define mp make_pair
#define F first
#define S second

#define FOR(i,a,b) for (int i = (a); i <= (b); ++i)
#define FOD(i,a,b) for (int i = (a); i >= (b); --i)

#define fillchar(a,x) memset(a, x, sizeof(a))
#define faster ios::sync_with_stdio(false); cin.tie(NULL);

const int N = 100005;
const ll INF = 1LL << 60;
const ll MOD = 1e9 + 7;

int vis[N], dis[N], path[N], mx[N], mn[N];
priority_queue<ii> pq;
vi adj2[N];
vii adj[N];
bool visited[N];
vi topo;

void dijkstra(int s) {
    FOR(i, 1, N - 1) dis[i] = INF;
    dis[s] = 0;
    pq.push({0, s});
    while (!pq.empty()) {
        int u = pq.top().S; pq.pop();
        if (vis[u]) continue;
        vis[u] = 1;
        for (auto [v, w] : adj[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push({-dis[v], v});
            }
        }
    }
}

void dfs(int u) {
    if (visited[u]) return;
    visited[u] = true;
    for (int v : adj2[u]) dfs(v);
    topo.pb(u);
}

void solve() {
    int n, m;
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].pb({v, w});
    }

    dijkstra(1);

    FOR(u, 1, n) {
        for (auto [v, w] : adj[u]) {
            if (dis[v] == dis[u] + w) {
                adj2[v].pb(u);
            }
        }
    }

    FOR(i, 1, n) {
        if (!visited[i]) dfs(i);
    }

    vi order;
    bool found = false;
    for (int i : topo) {
        if (i == 1) found = true;
        if (found) order.pb(i);
    }

    FOR(i, 1, n) mn[i] = INF;
    path[1] = mx[1] = mn[1] = 1;

    for (int u : order) {
        for (int v : adj2[u]) {
            (path[u] += path[v]) %= MOD;
            if (mn[v]) mn[u] = min(mn[u], mn[v] + 1);
            if (mx[v]) mx[u] = max(mx[u], mx[v] + 1);
        }
    }

    cout << dis[n] << ' ' << path[n] << ' ' << mn[n] - 1 << ' ' << mx[n] - 1 << '\n';
}

signed main() {
    faster;
    int t = 1;
    // cin >> t;
    while (t--) solve();
}
