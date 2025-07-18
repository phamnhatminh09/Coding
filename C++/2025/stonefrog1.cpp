#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n;
    cin >> n;
    vector<int> h(n);
    
    for (int i = 0; i < n; ++i) cin >> h[i];
    
    vector<int> dp(n);
    dp[0] = 0;
    if (n > 1) dp[1] = abs(h[1] - h[0]);
    
    for (int i = 2; i < n; ++i) dp[i] = min(dp[i - 1] + abs(h[i] - h[i - 1]), dp[i - 2] + abs(h[i] - h[i - 2]));
    
    cout << dp[n - 1];
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}