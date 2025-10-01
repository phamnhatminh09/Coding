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

int m, n;
vector<vector<int>> grid;
vector<vector<ii>> f;

ii cnt(int x) {
	int cnt2 = 0, cnt5 = 0;
	
	while (x % 2 == 0) {
		cnt2++;
		x /= 2;
	}
	
	while (x % 5 == 0) {
		cnt5++;
		x /= 5;
	}
	
	return {cnt2, cnt5};
}

int dijkstra(int type) {
	vector<vector<int>> d(m, vector<int>(n, oo));
	priority_queue<iii, vector<iii>, greater<iii>> pq;
	d[0][0] = (type == 0) ? f[0][0].first : f[0][0].second;
	pq.push({d[0][0], {0, 0}});
	
	while (!pq.empty()) {
		int du = pq.top().first, x = pq.top().second.first, y = pq.top().second.second;
		pq.pop();
		
		if (du > d[x][y]) continue;
		
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			
			if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
				int w = du + ((type == 0) ? f[nx][ny].first : f[nx][ny].second);
				
				if (d[nx][ny] > w) {
					d[nx][ny] = w;
					pq.push({w, {nx, ny}});
				}
			}
		}
	}
	
	return d[m - 1][n - 1];
}

void Solve() {
	cin >> m >> n;
	
	grid.resize(m, vector<int>(n));
	f.resize(m, vector<ii>(n));
	
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) {
			cin >> grid[i][j];
			f[i][j] = cnt(grid[i][j]);
		}
	}
	
	cout << min(dijkstra(0), dijkstra(1));
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}