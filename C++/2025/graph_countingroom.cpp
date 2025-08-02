#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void Solve() {
	int n, m;
	cin >> n >> m;
	
	vector<string> grid(n);
	for (int i = 0; i < n; ++i) cin >> grid[i];
	
	vector<vector<bool>> visited(n, vector<bool>(m, false));
	int res = 0;
	
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (grid[i][j] == '.' && !visited[i][j]) {
				queue<pair<int, int>> q;
				q.push({i, j});
				
				visited[i][j] = true;
				res++;
				
				while (!q.empty()) {
					auto [x, y] = q.front();
					q.pop();
					
					for (int k = 0; k < 4; ++k) {
						int nx = x + dx[k], ny = y + dy[k];
						
						if (nx >= 0 && nx < n && ny >= 0 && ny < m && grid[nx][ny] == '.' && !visited[nx][ny]) {
							visited[nx][ny] = true;
							q.push({nx, ny});
						}
					}
				}
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