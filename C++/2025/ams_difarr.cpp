#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

void Solve() {
	int n, k;
	cin >> n >> k;
    
    vector<ll> a(n);
    
    for (int i = 0; i < n; i++) cin >> a[i];
    
    vector<ll> prefix(n + 1, 0);
    for (int i = 1; i <= n; i++) prefix[i] = prefix[i - 1] + a[i - 1];
    
    ll sum0 = prefix[k] - prefix[0], minn = sum0, maxx = sum0, ans = 0;
    
    for (int i = k; i <= n - k; i++) {
        ll sum2 = prefix[i + k] - prefix[i];
        ans = max(ans, llabs(sum2 - minn));
        ans = max(ans, llabs(sum2 - maxx));
        ll sum1 = prefix[i] - prefix[i - k];
        minn = min(minn, sum1);
        maxx = max(maxx, sum1);
    }

    cout << ans;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}