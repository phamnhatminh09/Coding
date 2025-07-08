#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 250;

char c[N][N];
ll a[N][N], b[N][N], x[N][N], y[N][N], z[N][N];

void Solve() {
	ll n;
    cin >> n;
    
    for (ll i = 0; i <= n - 1; i++) {
        for (ll j = 0; j <= n - 1; j++) cin >> c[i][j];
    }
    
    for (ll i = 0;i <= n - 1; i++) {
        ll cnt = 0;
        for (ll j = 0; j <= n - 1; j++) {
            if (c[i][j]=='#') cnt++;
            a[i][j] = cnt;
        }
    }
    
    for (ll i = 0; i <= n - 1; i++) {
        for (ll j = n - 1; j >= 0; j--) {
            ll sum = 0;
            for (ll m = 0; m <= i; m++) {
                if (j == 0) sum += a[m][n - 1];
                else sum += a[m][n - 1] - a[m][j - 1];
            }
            x[i][j] = sum;
        }
    }
    
    for(ll i = n - 1; i >= 0; i--) {
        for(ll j = 0; j <= n - 1; j++) {
            ll sum = 0;
            for(ll m = n - 1; m >= i; m--) sum += a[m][j];
            y[i][j] = sum;
        }
    }
    
    for (ll i = n - 1; i >= 0; i--) {
        for (ll j = n - 1; j >= 0; j--) {
            ll sum = 0;
            for (ll m = n - 1; m >= i; m--) {
                if (j == 0) sum += a[m][n - 1];
                else sum += a[m][n - 1] - a[m][j - 1];
            }
            z[i][j] = sum;
        }
    }
    
    for (ll i = 0; i <= n - 1; i++) {
        for (ll j = 0; j <= n - 1; j++) {
            ll sum = 0;
            for (ll m = 0; m <= i; m++) {
                sum += a[m][j];
            }
            b[i][j] = sum;
        }
    }
    
    ll res = 0, row = 0,col = 0;
    for (ll i = 1; i <= n - 2; i++) {
        for (ll j = 1; j <= n - 2; j++) {
            ll temp = min(b[i][j], min(x[i][j + 1], min(y[i + 1][j], z[i + 1][j + 1])));
            if (temp > res) {
                res = temp;
                row = i;
                col = j;
            }
        }
    }
    cout << res << '\n' << 'R' << " " << row + 1 << '\n' << 'C' << " " << col + 1;
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}