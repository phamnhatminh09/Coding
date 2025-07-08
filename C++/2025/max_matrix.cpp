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

    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> mat[i][j];
    }
    
    vector<vector<int>> pre(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) pre[i][j] = mat[i - 1][j - 1] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
    }

    int res = INT_MIN;
    
    for (int x1 = 1; x1 <= n; ++x1) {
        for (int y1 = 1; y1 <= m; ++y1) {
            for (int x2 = x1; x2 <= n; ++x2) {
                for (int y2 = y1; y2 <= m; ++y2) {
                    int temp = pre[x2][y2] - pre[x1 - 1][y2] - pre[x2][y1 - 1] + pre[x1 - 1][y1 - 1];
                    if (temp > res) res = temp;
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