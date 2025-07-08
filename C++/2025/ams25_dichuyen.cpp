#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> pii;

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

bool check(const vector<vector<int>>& g, int n, int m, int x1, int y1, int x2, int y2) {
    if (g[x1][y1] != g[x2][y2]) return false;

    vector<vector<bool>> v(n, vector<bool>(m, false));
    queue<pii> q;
    q.push({x1, y1});
    v[x1][y1] = true;

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();

        if (x == x2 && y == y2) return true;

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < n && ny >= 0 && ny < m && !v[nx][ny] && g[nx][ny] == g[x][y]) {
                v[nx][ny] = true;
                q.push({nx, ny});
            }
        }
    }

    return false;
}

string solve(const vector<vector<int>>& g, int n, int m, int x1, int y1, int x2, int y2) {
    if (check(g, n, m, x1, y1, x2, y2)) return "YES";
    
    if (g[x1][y1] != g[x2][y2]) {
        vector<vector<int>> temp = g;
        temp[x1][y1] = temp[x2][y2];
        if (check(temp, n, m, x1, y1, x2, y2)) return "YES";
    }
    
    if (g[x1][y1] != g[x2][y2]) {
        vector<vector<int>> temp = g;
        temp[x2][y2] = temp[x1][y1];
        if (check(temp, n, m, x1, y1, x2, y2)) return "YES";
    }
    
    for (int i = 0; i < 4; ++i) {
        int nx = x1 + dx[i];
        int ny = y1 + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] != g[x2][y2]) {
            vector<vector<int>> temp = g;
            temp[nx][ny] = temp[x2][y2];
            if (check(temp, n, m, x1, y1, x2, y2)) return "YES";
        }
    }
    
    for (int i = 0; i < 4; ++i) {
        int nx = x2 + dx[i];
        int ny = y2 + dy[i];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] != g[x1][y1]) {
            vector<vector<int>> temp = g;
            temp[nx][ny] = temp[x1][y1];
            if (check(temp, n, m, x1, y1, x2, y2)) return "YES";
        }
    }

    return "NO";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;

    vector<vector<int>> g(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> g[i][j];
        }
    }

    int q, dummy;
    cin >> q >> dummy;
    
    while (q--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << solve(g, n, m, x1, y1, x2, y2) << '\n';
    }

    return 0;
}