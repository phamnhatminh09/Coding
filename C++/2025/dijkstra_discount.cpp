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

vector<vector<ll>> d(N + 1, vector<ll>(2, oo));
vector<vector<ii>> adj(N + 1);
int n, m;

void dijkstra () {
	d[1][0] = d[1][1] = 0;
	priority_queue<pair<ll, ii>, vector<pair<ll, ii>>, greater<pair<ll, ii>>> pq;
	pq.push({0, {1, 0}});
	pq.push({0, {1, 1}});
	
	while (!pq.empty()) {
		ll du = pq.top().first;
		int u = pq.top().second.first, used = pq.top().second.second;
		pq.pop();
		
		if (du != d[u][used]) continue;
		
		for (auto [v, w] : adj[u]) {
			if (used == 0) {
				if (d[v][0] > du + w) {
					d[v][0] = du + w;
					pq.push({d[v][0], {v, 0}});
				}
				if (d[v][1] > du + (int) floor(w / 2)) {
					d[v][1] = du + (int) floor(w / 2);
					pq.push({d[v][1], {v, 1}});
				}
			}
			if (d[v][used] > du + w) {
				d[v][used] = du + w;
				pq.push({d[v][used], {v, used}});
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
	
	cout << min(d[n][0], d[n][1]);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}