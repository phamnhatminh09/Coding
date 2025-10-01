
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const ll oo = 1e9;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int dijkstra(int n, int m, const vector<vector<char>>& grid, ii xy, ii uv) {
	vector<vector<int>> d(n, vector<int> (m, INT_MAX));
	priority_queue<pair<int, ii>, vector<pair<int, ii>>, greater<pair<int, ii>>> pq;
	
	d[xy.first][xy.second] = 0;
	pq.push({0, xy});
	
	while (!pq.empty()) {
		int du = pq.top().first, x = pq.top().second.first, y = pq.top().second.second;
		pq.pop();
		
		if (x == uv.first && y == uv.second) return du;
		
		if (du > d[x][y]) continue;
		
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			
			if (nx >= 0 && nx < n && ny >= 0 && ny < n) {
				int v = (grid[nx][ny] == 'G' || grid[nx][ny] == 'R') ? 0 : (grid[nx][ny] - '0');
				
				if (du + v < d[nx][ny]) {
					d[nx][ny] = du + v;
					pq.push({du + v, {nx, ny}});
				}
			}
		}
	}
	
	return -1;
}

void Solve() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<char>> grid(n, vector<char>(n));
	ii xy, uv;
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> grid[i][j];
			if (grid[i][j] == 'G') xy = {i, j};
			else if (grid[i][j] == 'R') uv = {i, j};
		}
	}
	
	cout << dijkstra(n, m, grid, xy, uv);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}