#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const int maxn = 1e5 + 69;
const int K = 21;
const ll INF = 1e18;
const ll mod = 1e9 + 7;

ll maxs[K][maxn], mins[K][maxn];
int lg2[maxn];

void sparse(int n, vector<ll>& t) {
    lg2[1] = 0;
    for(int i = 2; i <= n; i++) lg2[i] = lg2[i >> 1] + 1;
    
    for(int i = 1; i <= n; i++) {
    	maxs[0][i] = t[i];
    	mins[0][i] = t[i];
    }
    
    for(int k = 1; k < K; k++) {
        int len = 1 << k;
        for(int i = 1; i + len - 1 <= n; i++) {
            maxs[k][i] = max(maxs[k - 1][i], maxs[k - 1][i + (len >> 1)]);
            mins[k][i] = min(mins[k - 1][i], mins[k - 1][i + (len >> 1)]);
        }
    }
}

ll maxx(int l, int r) {
    int len = r - l + 1;
    int k = lg2[len];
    return max(maxs[k][l], maxs[k][r - (1 << k) + 1]);
}

ll minn(int l, int r) {
	int len = r - l + 1;
	int k = lg2[len];
	return min(mins[k][l], mins[k][r - (1 << k) + 1]);
}

void Solve() {
	int n, k;
    cin >> n >> k;
    
    vector<ll> a(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    sparse(n, a);
    vector<vector<ll>> dp(k + 2, vector<ll>(n + 2));
    for (int x = 0; x <= k; x++) {
    	for (int i = 0; i <= n; i++) dp[x][i] = -INF;
    }
    
    for (int i = 1; i <= n; i++) dp[1][i] = maxx(1, i) + minn(1, i);
    
    for (int x = 2; x <= k; x++) {
        for (int i = x; i <= n; i++) {
            ll best = -INF;
            for (int j = x; j <= i; j++) {
                ll c = maxx(j, i) + minn(j, i);
                best = max(best, dp[x - 1][j - 1] + c);
            }
            
            dp[x][i] = best;
        }
    }

    cout << dp[k][n];
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}