#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<int>> adj, dp;

void dfs(int u, int parent) {
    dp[u][0] = 0;
    dp[u][1] = 1;

    for (int v : adj[u]) {
        if (v == parent) continue;
        dfs(v, u);
        dp[u][0] += max(dp[v][0], dp[v][1]);
        dp[u][1] += dp[v][0];
    }
}

void Solve() {
	int n;
    cin >> n;
    
    adj.resize(n + 1);
    dp.assign(n + 1, vector<int>(2, 0));

    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1, -1);

    cout << max(dp[1][0], dp[1][1]);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}