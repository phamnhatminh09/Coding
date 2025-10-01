#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, k;
    cin >> n >> k;
    
    vector<int> h(n + 1);
    for (int i = 1; i <= n; ++i) cin >> h[i];
    
    vector<int> dp(n + 1, INT_MAX);
    dp[1] = 0;

    for (int i = 2; i <= n; ++i) {
        for (int j = 1; j <= k; ++j) {
            if (i - j >= 1) dp[i] = min(dp[i], dp[i - j] + abs(h[i] - h[i - j]));
        }
    }

    cout << dp[n];
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}