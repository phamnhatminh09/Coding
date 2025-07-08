#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
#define endl '\n'
const ll N = 1e5 + 5;
const int mod = 1e9 + 7;
int n, m;
ll dp[121][121][2];
bool vis[121][121][2];

ll go(int pos, int sum, bool pre) {
    if (pos == n) return sum == 0 ? 1 : 0;
    if (vis[pos][sum][pre]) return dp[pos][sum][pre];
    vis[pos][sum][pre] = true;
    
    ll res = 0;
    for (int d = 0; d <= 9; ++d) {
        if (d > sum) break;
        if (pre && d == 3) continue;
        res = (res + go(pos + 1, sum - d, d == 1)) % mod;
    }
    return dp[pos][sum][pre] = res;
}

void Solve() {
    int t;
    cin >> t;
    while (t--) {
        cin >> n >> m;
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= m; ++j)
                vis[i][j][0] = vis[i][j][1] = false;

        cout << go(0, m, false) << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}