#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "a", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e6 + 6;

ll a[N][10];
ll check(ll x) {
    ll res = 0;
    
    while(x > 0) {
        x = x / 10;
        res++;
    }
    
    return res;
}

void Solve() {
	ll n, k, x;
	cin >> n >> k;
	
    for (ll i = 1; i <= n; i++) {
        cin >> x;
        x %= k;
        for (ll j = 1; j <= 6; j++) {
            x *= 10;
            x %= k;
            a[x][j]++;
        }
    }
    
    ll res = 0;
    for (ll i = 1; i <= n; i++) {
        cin >> x;
        ll cnt = check(x);
        x %= k;
        ll tmp = k - x;
        tmp %= k;
        res += a[tmp][cnt];
    }
    
    cout << res;
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}