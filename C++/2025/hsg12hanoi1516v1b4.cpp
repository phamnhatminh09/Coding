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
const ll oo = 1e18;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void Solve() {
	int m, n, x1, y1, x2, y2;
	cin >> m >> n >> x1 >> y1 >> x2 >> y2;
	
	x1--;
	y1--;
	x2--;
	y2--;
	
	vector<vector<int>> grid(m, vector<int> (n));
	for (int i = 0; i < m; ++i) {
		for (int j = 0; j < n; ++j) cin >> grid[i][j];
	}
	
	priority_queue<iii, vector<iii>, greater<iii>> pq;
	vector<vector<int>> minn(m, vector<int>(n, INT_MAX));
	pq.push({0, {x1, y1}});
	minn[x1][y1] = 0;
	
	while (!pq.empty()) {
		int du = pq.top().first, x = pq.top().second.first, y = pq.top().second.second;
		pq.pop();
		
		if (x == x2 && y == y2) {
			cout << du << '\n';
			return;
		}
		
		if (du > minn[x][y]) continue;
		
		for (int i = 0; i < 4; ++i) {
			int nx = x + dx[i], ny = y + dy[i];
			
			if (nx >= 0 && nx < m && ny >= 0 && ny < n) {
				int w = max(du, abs(grid[nx][ny] - grid[x][y]));
				
				if (minn[nx][ny] > w) {
					minn[nx][ny] = w;
					pq.push({w, {nx, ny}});
				}
			}
		}
	}
	
	cout << minn[x2][y2];
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}