#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m, k;
	cin >> n >> m >> k;
	
	vector<vector<int>> g(n + 1);
	for (int i = 0; i < m; ++i) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	unordered_set<string> trip;
	for (int i = 0; i < k; ++i) {
		int a, b, c;
		cin >> a >> b >> c;
		trip.insert(to_string(a) + "," + to_string(b) + "," + to_string(c));
	}
	
	vector<vector<int>> dist(n + 1, vector<int> (n + 1, -1));
	queue<tuple<int, int, int>> q;
	q.push({0, 1, 0});
	dist[0][1] = 0;
	
	int res = -1;
	
	while (!q.empty()) {
		auto [prev, curr, d] = q.front();
		q.pop();
		
		if (curr == n) {
			res = d;
			break;
		}
		
		for (int x : g[curr]) {
			string key = to_string(prev) + "," + to_string(curr) + "," + to_string(x);
			if (trip.find(key) == trip.end() && dist[curr][x] == -1) {
				dist[curr][x] = d + 1;
				q.push({curr, x, d + 1});
			}
		}
	}
	
	cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}