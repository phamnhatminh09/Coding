#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	ll n, m;
    cin >> n >> m;

    vector<pair<pair<ll, ll>, ll>> v(m);
    for (ll i = 0; i < m; ++i) {
        ll l, r;
        ll x;
        cin >> l >> r >> x;
        v[i] = {{l, r}, x};
    }

    vector<ll> a(n + 2, 0);
    for (const auto& op : v) {
        ll l = op.first.first, r = op.first.second, x = op.second;
        
        a[l] += x;
        if (r + 1 <= n) a[r + 1] -= x;
    }

    vector<ll> b(n + 1, 0);
    ll curr = 0, val = 0;
    for (ll i = 1; i <= n; ++i) {
        curr += a[i];
        b[i] = curr;
        
        if (curr > val) val = curr;
    }

    vector<ll> v1(n + 2, 0), v2(n + 2, 0);
    for (ll i = 1; i <= n; ++i) v1[i] = max(v1[i - 1], b[i]);
    for (ll i = n; i >= 1; --i) v2[i] = max(v2[i + 1], b[i]);
    ll res = LLONG_MAX;
    for (const auto& op : v) {
        ll l = op.first.first, r = op.first.second, x = op.second, y = max(v1[l - 1], v2[r + 1]), temp = 0;
        
        for (ll i = l; i <= r; ++i) {
            if (b[i] - x > temp) temp = b[i] - x;
        }
        
        y = max(y, temp);
        if (y < res) res = y;
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