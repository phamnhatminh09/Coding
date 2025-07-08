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
	
    vector<vector<char>> g(n, vector<char>(m));
    pair<int, int> st, en;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
            if (g[i][j] == 'S') st = {i, j};
            else if (g[i][j] == 'T') en = {i, j};
        }
    }
    
    vector<vector<int>> d(n, vector<int> (m, -1));
    queue<pair<int, int>> q;
    q.push(st);
    d[st.first][st.second] = 0;
    
    int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
    
    while (!q.empty()) {
    	auto temp = q.front();
    	q.pop();
    	int x = temp.first, y = temp.second;
    	
    	if (x == en.first && y == en.second) {
    		cout << d[x][y];
    		break;
    	}
    	
    	for (int i = 0; i < 4; ++i) {
    		int nx = x + dx[i], ny = y + dy[i];
    		
    		if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
    			if (g[nx][ny] != '*' && d[nx][ny] == -1) {
    				d[nx][ny] = d[x][y] + 1;
                    q.push({nx, ny});
    			}
    		}
    	}
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}