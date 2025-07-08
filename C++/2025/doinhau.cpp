#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<pair<int, int>>> adj;
vector<vector<int>> dist;

void bfs(int st, int n) {
    dist[st].resize(n + 1, -1);
    queue<int> q;
    q.push(st);
    dist[st][st] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto &ee : adj[u]) {
            int v = ee.first;
            int w = ee.second;
            if (dist[st][v] == -1) {
                dist[st][v] = dist[st][u] + w;
                q.push(v);
            }
        }
    }
}

void Solve() {
	int n;
    cin >> n;
    adj.resize(n + 1);
    dist.resize(n + 1);

    for (int i = 0; i < n - 1; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v, w);
        adj[v].emplace_back(u, w);
    }

    for (int i = 1; i <= n; ++i) bfs(i, n);

    long long tot = 0, cnt = 0;

    for (int u = 1; u <= n; ++u) {
        for (int v = u + 1; v <= n; ++v) {
            if (gcd(u, v) == 1) {
                tot += dist[u][v];
                cnt++;
            }
        }
    }

    double average = (cnt == 0) ? 0 : (double) tot / cnt;
    cout << fixed << setprecision(4) << average;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}