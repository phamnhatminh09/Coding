#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n;
    string s;
    ll a, b, c;
    
    cin >> n >> s >> a >> b >> c;
    
    unordered_set<string> seen;
    vector<ll> dp(n + 1, 1e18);
    dp[0] = 0;
    
    for (int i = 1; i <= n; i++) {
        dp[i] = dp[i - 1] + a;
        
        for (int len = 1; len <= i / 2; len++) {
            string l = s.substr(i - 2 * len, len), r = s.substr(i - len, len);
            
            if (l == r) dp[i] = min(dp[i], dp[i - len] + b);
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