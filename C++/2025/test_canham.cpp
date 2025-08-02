#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

struct st {
    int x, y, r, t;
};

int q, n, k, m;
vector<st> v;
int xs, ys, xt, yt;

bool check(int x, int y, int step) {
    for (const auto& q : v) {
        int curr = (q.t + step) % q.r, dist = abs(x - q.x) + abs(y - q.y);
    	
    	if (dist <= curr) return true;
    }
    
    return false;
}

int q1() {
    int res = 0;
    
    for (int step = 0; step <= m; ++step) {
        int covered = 0;
        
        for (int x = 1; x <= n; ++x) {
            for (int y = 1; y <= n; ++y) {
                if (check(x, y, step)) covered++;
            }
        }
        
        res = max(res, covered);
    }
    
    return res;
}

int q2() {
    vector<vector<int>> dist(n + 1, vector<int>(n + 1, -1));
    queue<pair<int, int>> q;
    if (!check(xs, ys, 0)) {
        q.push({xs, ys});
        dist[xs][ys] = 0;
    }

    int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};

    while (!q.empty()) {
        auto [x, y] = q.front();
        q.pop();
        if (x == xt && y == yt) return dist[x][y];
        
        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i], ny = y + dy[i];
            
            if (nx >= 1 && nx <= n && ny >= 1 && ny <= n && dist[nx][ny] == -1) {
                int temp = dist[x][y] + 1;
                if (!check(nx, ny, temp)) {
                    
                    dist[nx][ny] = temp;
                    q.push({nx, ny});
                }
            }
        }
    }
    
    return -1;
}

void Solve() {
	cin >> q >> n >> k >> m;
    v.resize(k);
    
    for (int i = 0; i < k; ++i) cin >> v[i].x >> v[i].y >> v[i].r >> v[i].t;
    cin >> xs >> ys >> xt >> yt;

    if (q == 1) cout << q1() << '\n';
    else cout << q2() << '\n';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}