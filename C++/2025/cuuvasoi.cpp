#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void bfs(int i, int j, vector<vector<char>>& g, vector<vector<bool>>& v, int& s, int& w, bool& check) {
    int n = g.size(), m = g[0].size();
    queue<pair<int, int>> q;
    q.push({i, j});
    v[i][j] = true;
    
    if (g[i][j] == 'k') s++;
    if (g[i][j] == 'v') w++;

    while (!q.empty()) {
        auto curr = q.front();
        q.pop();
        int x = curr.first, y = curr.second;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k], ny = y + dy[k];

            if (nx < 0 || nx >= n || ny < 0 || ny >= m) {
                check = false;
                continue;
            }

            if (g[nx][ny] != '#' && !v[nx][ny]) {
                v[nx][ny] = true;
                q.push({nx, ny});
                if (g[nx][ny] == 'k') s++;
                if (g[nx][ny] == 'v') w++;
            }
        }
    }
}

void Solve() {
	int n, m;
    cin >> n >> m;
    
    vector<vector<char>> g(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) cin >> g[i][j];
    }

    vector<vector<bool>> v(n, vector<bool>(m, false));
    int sh = 0, wol = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] != '#' && !v[i][j]) {
                int s = 0, w = 0;
                bool check = true;
                bfs(i, j, g, v, s, w, check);

                if (check) {
                    if (s > w) sh += s;
                    else wol += w;
                }
                else {
                    sh += s;
                    wol += w;
                }
            }
        }
    }

    cout << sh << " " << wol << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}