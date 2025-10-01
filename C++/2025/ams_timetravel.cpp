#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;
typedef pair<ll, ii> lli;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 2e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n, m;
vector<vector<pair<ii, ii>>> adj;
vector<int> a;
vector<ll> dist(N + 1, oo);

void dijkstra() {
	priority_queue<lli, vector<lli>, greater<lli>> pq;
	vector<bool> visited(m, false);
	pq.push({0, {1, -1}});
	dist[1] = 0;
	
	while (!pq.empty()) {
		int du = pq.top().first, u = pq.top().second.first, index = pq.top().second.second;
        pq.pop();

        if (index == -1) {
            for (auto& node : adj[u]) {
                int r = node.first.first, d = node.first.second, s = node.second.first, i = node.second.second;
                if (du <= r && !visited[i]) {
                    visited[i] = true;
                    pq.push({s, {d, i}});
                }
            }
        }
        else {
            int v = u;
            if (dist[v] > du) {
                dist[v] = du;
                pq.push({du + a[v], {v, -1}});
            }
        }
	}
}

void Solve() {
	cin >> n >> m;
	
	adj.resize(n + 1);
	a.resize(n + 1);
	for (int i = 0; i < m; ++i) {
		int c, r, d, s;
		cin >> c >> r >> d >> s;
		adj[c].push_back({{r, d}, {s, i}});
	}
	
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	dijkstra();
	
	for (int i = 1; i <= n; ++i) {
		if (dist[i] == oo) cout << -1 << '\n';
		else cout << dist[i] << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}