#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> g(n + 1);
	while (m--) {
		int u, v;
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	
	int q;
	cin >> q;
	
	vector<tuple<int, int, int>> qu(q);
    for (int i = 0; i < q; ++i) {
        int u, d, c;
        cin >> u >> d >> c;
        qu[i] = {u, d, c};
    }
	
	vector<int> color(n + 1, 0);
	for (int i = q - 1; i >= 0; --i) {
		auto [u, d, c] = qu[i];
		
		queue<pair<int, int>> q_bfs;
        vector<bool> v(n + 1, false);
        q_bfs.push({u, 0});
        v[u] = true;

        while (!q_bfs.empty()) {
            auto [curr, dist] = q_bfs.front();
            q_bfs.pop();

            if (color[curr] == 0) color[curr] = c;
            if (dist == d) continue;

            for (int x : g[curr]) {
                if (!v[x]) {
                    v[x] = true;
                    q_bfs.push({x, dist + 1});
                }
            }
        }
	}
	
	for (int i = 1; i <= n; ++i) cout << color[i] << '\n';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}