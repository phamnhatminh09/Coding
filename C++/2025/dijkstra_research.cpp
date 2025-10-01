#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const ll oo = 1e18;
const ll mod = 1e9 + 7;

int n, m;
vector<vector<ii>> adj(N + 1);
vector<ll> d(N + 1, oo), cnt(N + 1, 0);
vector<int> minn(N + 1, INT_MAX), maxx(N + 1, -1);

void dijkstra() {
	d[1] = minn[1] = maxx[1] = 0;
	cnt[1] = 1;
	priority_queue<li, vector<li>, greater<li>> pq;
	pq.push({0, 1});
	
	while (!pq.empty()) {
		ll du = pq.top().first;
		int u = pq.top().second;
		pq.pop();
		
		if (du > d[u]) continue;
		
		for (auto node : adj[u]) {
			int v = node.first, w = node.second;
			
			if (d[v] > d[u] + w) {
				d[v] = d[u] + w;
				cnt[v] = cnt[u];
				minn[v] = minn[u] + 1;
				maxx[v] = maxx[u] + 1;
				pq.push({d[v], v});
			}
			else if (d[v] == d[u] + w) {
				cnt[v] = ((cnt[v] % mod) + (cnt[u] % mod)) % mod;
				minn[v] = min(minn[v], minn[u] + 1);
				maxx[v] = max(maxx[v], maxx[u] + 1);
			}
		}
	}
}

void Solve() {
	cin >> n >> m;
	
	for (int i = 0; i < m; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		adj[a].emplace_back(b, c);
	}
	
	dijkstra();
	cout << d[n] << ' ' << cnt[n] << ' ' << minn[n] << ' ' << maxx[n];
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}