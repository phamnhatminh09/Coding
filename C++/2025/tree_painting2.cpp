#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const int mod = 1e9 + 7;
vector<vector<int>> adj;
vector<int> ban;
vector<vector<long long>> dp;

void dfs(int u, int par) {
    for (int c = 1; c <= 3; ++c) {
        if (ban[u] == c) dp[u][c] = 0;
        else dp[u][c] = 1;
    }

    for (int v : adj[u]) {
        if (v == par) continue;
        dfs(v, u);
        for (int c = 1; c <= 3; ++c) {
            long long sum = 0;
            
            for (int d = 1; d <= 3; ++d) {
                if (c != d) sum += dp[v][d];
            }
            
            dp[u][c] = (dp[u][c] * sum) % mod;
        }
    }
}

void Solve() {
	int n, k;
    cin >> n >> k;
    
    adj.resize(n + 1);
    ban.resize(n + 1, 0);
    dp.assign(n + 1, vector<long long>(4, 0));
    
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    
    for (int i = 0; i < k; ++i) {
        int v, c;
        cin >> v >> c;
        ban[v] = c;
    }

    dfs(1, -1);

    long long ans = 0;
    for (int c = 1; c <= 3; ++c) ans = (ans + dp[1][c]) % mod;

    cout << ans;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}