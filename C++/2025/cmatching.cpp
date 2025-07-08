#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 3005;
const int mod = 1e9 + 7;

vector<int> adj[N];
int dp[N][N][2], temp[N][2], n, k;

void dfs(int u, int par) {
    dp[u][0][0] = 1;
    
    for (int v : adj[u]) {
        if (v == par) continue;
        dfs(v, u);
        
        memset(temp, 0, sizeof(temp));
        
        for (int i = 0; i <= k; ++i) {
            for (int j = 0; j <= k - i; ++j) {
                temp[i + j][0] = (temp[i + j][0] + 1LL * dp[u][i][0] * (dp[v][j][0] + dp[v][j][1]) % mod) % mod;
                temp[i + j][1] = (temp[i + j][1] + 1LL * dp[u][i][1] * (dp[v][j][0] + dp[v][j][1]) % mod) % mod;
                if (i + j + 1 <= k) {
                    temp[i + j + 1][1] = (temp[i + j + 1][1] + 1LL * dp[u][i][0] * dp[v][j][0] % mod) % mod;
                }
            }
        }
        
        for (int i = 0; i <= k; ++i) {
            dp[u][i][0] = temp[i][0];
            dp[u][i][1] = temp[i][1];
        }
    }
}

void Solve() {
	cin >> n >> k;
	
    for (int i = 0; i < n - 1; ++i) {
        int x, y;
        cin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    dfs(1, -1);

    cout << (dp[1][k][0] + dp[1][k][1]) % mod;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}