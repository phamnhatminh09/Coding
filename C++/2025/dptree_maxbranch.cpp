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
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    
    vector<int> v(n + 1);
    for (int i = 1; i <= n; ++i) cin >> v[i];
    
    vector<long long> dp(n + 1, 0);
    dp[1] = a[1];
    long long res = dp[1];
    
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[v[i]] + a[i];
        res = max(res, dp[i]);
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