#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const int MAX = 1e6 + 5;
vector<bool> isp(MAX, true);

void sieve() {
    isp[0] = isp[1] = false;
    for (int i = 2; i * i < MAX; ++i) {
        if (isp[i]) {
            for (int j = i * i; j < MAX; j += i) isp[j] = false;
        }
    }
}

void Solve() {
	sieve();

    int m, n;
    cin >> m >> n;
    vector<vector<int>> grid(m, vector<int>(n)), psum(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> grid[i][j];
            psum[i + 1][j + 1] = psum[i][j + 1] + psum[i + 1][j] - psum[i][j] + (isp[grid[i][j]] ? 0 : 1);
        }
    }

    int res = 0;
    for (int i = 1; i <= m; ++i) {
        for (int j = 1; j <= n; ++j) {
            int temp = min(m - i + 1, n - j + 1);
            for (int k = temp; k >= 1; --k) {
                if (k * k <= res) break;
                int x = psum[i + k - 1][j + k - 1] - psum[i - 1][j + k - 1] - psum[i + k - 1][j - 1] + psum[i - 1][j - 1];
                if (x <= 1) {
                    res = max(res, k * k);
                    break;
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