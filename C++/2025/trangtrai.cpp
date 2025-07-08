#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll n = 1e5 + 5;

bool check(const vector<int>& cw, int n, int l, int r, int k, int x) {
    vector<int> psum(n + 1, 0), dp(n + 1, -1);
    for (int i = 1; i <= n; ++i) psum[i] = psum[i - 1] + cw[i - 1];
    
    dp[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = max(0, i - r); j <= i - l; ++j) {
            if (dp[j] != -1) {
                int sum = psum[i] - psum[j], len = i - j;
                
                if (sum >= x * len) {
                    if (dp[i] < dp[j] + 1) dp[i] = dp[j] + 1;
                }
            }
        }
        
        if (dp[i] >= k) return true;
    }
    
    return false;
}

int bs(int n, int l, int r, int k, const vector<int>& cw) {
    int rt = accumulate(cw.begin(), cw.end(), 0), lt = 0, result = 0;

    while (lt <= rt) {
        int m = (lt + rt) / 2;
        
        if (check(cw, n, l, r, k, m)) {
            result = m;
            lt = m + 1;
        }
        
        else rt = m - 1;
    }
    
    return result;
}

void Solve() {
	int n, l, r, k;
    cin >> n >> l >> r >> k;
    
    vector<int> cw(n);
    for (int i = 0; i < n; ++i) cin >> cw[i];

    cout << bs(n, l, r, k, cw);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}