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
const int oo = 1e9;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int n, m;
vector<vector<int>> grid;

void dijkstra(int x, int y, vector<vector<int>>& d) {
	priority_queue<iii, vector<iii>, greater<iii>> pq;
	pq.push({grid[x - 1][y - 1], {x, y}});
	d[x][y] = grid[x - 1][y - 1];
	
	while (!pq.empty()) {
		int du = pq.top().first, x = pq.top().second.first, y = pq.top().second.second;
		pq.pop();
		
		if (du > d[x][y]) continue;
		
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			
			if (nx >= 1 && nx <= m && ny >= 1 && ny <= n) {
				int w = du + grid[nx - 1][ny - 1];
				
				if (d[nx][ny] > w) {
					d[nx][ny] = w;
					pq.push({w, {nx, ny}});
				}
			}
		}
	}
}

void Solve() {
	int x1, y1, x2, y2, x3, y3;
	cin >> m >> n >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	
	grid.resize(m, vector<int>(n));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) cin >> grid[i][j];
	}
	
	vector<vector<int>> d1(m + 1, vector<int>(n + 1, oo)), d2(m + 1, vector<int>(n + 1, oo)), d3(m + 1, vector<int>(n + 1, oo)), xd(m + 1, vector<int>(n + 1, oo));
	
	dijkstra(x1, y1, d1);
	dijkstra(x2, y2, d2);
	dijkstra(x3, y3, d3);
	dijkstra(1, 1, xd);
	
	int minn = oo;
	
	int c12 = xd[x1][y1] + d1[x2][y2] + d2[m][n] - grid[x1 - 1][y1 - 1] - grid[x2 - 1][y2 - 1], c21 = xd[x2][y2] + d2[x1][y1] + d1[m][n] - grid[x2 - 1][y2 - 1] - grid[x1 - 1][y1 - 1];
	minn = min({minn, c12, c21});
	
	int c13 = xd[x1][y1] + d1[x3][y3] + d3[m][n] - grid[x1 - 1][y1 - 1] - grid[x3 - 1][y3 - 1], c31 = xd[x3][y3] + d3[x1][y1] + d1[m][n] - grid[x3 - 1][y3 - 1] - grid[x1 - 1][y1 - 1];
	minn = min({minn, c13, c31});
	
	int c23 = xd[x2][y2] + d2[x3][y3] + d3[m][n] - grid[x2 - 1][y2 - 1] - grid[x3 - 1][y3 - 1], c32 = xd[x3][y3] + d3[x2][y2] + d2[m][n] - grid[x3 - 1][y3 - 1] - grid[x2 - 1][y2 - 1];
	minn = min({minn, c23, c32});
	
	cout << minn;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}