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
    for (int i = 1; i <= n; i++) cin >> a[i];
    
    const int MAXV = 1000005;
    vector<int> len(MAXV, 0), index(MAXV, 0), dp(n + 1), pr(n + 1);

    int mlen = 0, end = 0;
    for (int i = 1; i <= n; i++) {
        int val = a[i];
        if (val + 1 < MAXV && len[val + 1] > 0) {
            dp[i] = len[val + 1] + 1;
            pr[i] = index[val + 1];
        }
        else {
            dp[i] = 1;
            pr[i] = 0;
        }
        
        if (dp[i] > len[val]) {
            len[val] = dp[i];
            index[val] = i;
        }
        if (dp[i] > mlen) {
            mlen = dp[i];
            end = i;
        }
    }
    
    vector<int> res;
    for (int i = end; i != 0; i = pr[i]) res.push_back(i);
    reverse(res.begin(), res.end());
    
    cout << mlen << "\n";
    for (int i = 0; i < (int)res.size(); i++) cout << res[i] << (i + 1 < res.size() ? ' ' : '\n');
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}