#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;
typedef pair<int, ii> iii;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5;
const ll oo = 1e9;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n, m, x, y, z, t;

int dijkstra(const vector<vector<int>>& grid, vector<vector<int>> d, unordered_map<int, vector<ii>>& umap) {
	priority_queue<iii, vector<iii>, greater<iii>> pq;
    pq.push({0, {x, y}});
    d[x][y] = 0;

    while (!pq.empty()) {
        int du = pq.top().first, u = pq.top().second.first, v = pq.top().second.second;
        pq.pop();

        if (du > d[u][v]) continue;
        
        for (int i = 0; i < 4; ++i) {
            int nu = u + dx[i], nv = v + dy[i];
            
            if (nu >= 0 && nu < n && nv >= 0 && nv < m && grid[nu][nv] != 0) {
                if (d[nu][nv] > du + 1) {
                    d[nu][nv] = du + 1;
                    pq.push({d[nu][nv], {nu, nv}});
                }
            }
        }
        
        int val = grid[u][v];
        if (val == 0) continue;
        
        for (auto& x : umap[val]) {
            int nu = x.first, nv = x.second;
            
            if (nu == u && nv == v) continue;
            
            if (d[nu][nv] > du + 1) {
                d[nu][nv] = du + 1;
                pq.push({d[nu][nv], {nu, nv}});
            }
        }
        
        umap[val].clear();
    }
    
    return d[z][t];
}

void Solve() {
	cin >> n >> m >> x >> y >> z >> t;
	x--;
	y--;
	z--;
	t--;
	
	vector<vector<int>> grid(n, vector<int>(m));
	unordered_map<int, vector<ii>> umap;
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> grid[i][j];
			if (grid[i][j] != 0) umap[grid[i][j]].emplace_back(i, j);
		}
	}
	
	vector<vector<int>> d(n, vector<int>(m, oo));
	
	cout << dijkstra(grid, d, umap);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}