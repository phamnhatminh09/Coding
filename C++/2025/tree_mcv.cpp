#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const long long N = 1e18;
vector<vector<int>> adj;
vector<long long> a;
vector<vector<pair<int, long long>>> dp;

void dfs(int u, int par) {
    dp[u][0] = {0, 0};
    dp[u][1] = {1, a[u]};

    for (int v : adj[u]) {
        if (v == par) continue;
        dfs(v, u);
        
        dp[u][0].first += dp[v][1].first;
        dp[u][0].second += dp[v][1].second;
        
        if (dp[v][0].first < dp[v][1].first || (dp[v][0].first == dp[v][1].first && dp[v][0].second < dp[v][1].second)) {
            dp[u][1].first += dp[v][0].first;
            dp[u][1].second += dp[v][0].second;
        }
        else {
            dp[u][1].first += dp[v][1].first;
            dp[u][1].second += dp[v][1].second;
        }
    }
}


void Solve() {
	int n;
    cin >> n;
    a.resize(n + 1);
    adj.resize(n + 1);
    dp.assign(n + 1, vector<pair<int, long long>>(2, {0, 0}));

    for (int i = 1; i <= n; ++i) cin >> a[i];

    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1, -1);

    if (dp[1][0].first < dp[1][1].first || (dp[1][0].first == dp[1][1].first && dp[1][0].second < dp[1][1].second)) cout << dp[1][0].second << endl;
    else cout << dp[1][1].second << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}