#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll n, x;
vector<pair<ll, ll>> v;

ll cnt(ll t) {
    ll total = 0;
    
    for (auto &chicken : v) {
        ll p = chicken.first, q = chicken.second;
        if (t >= p) total += (t - p) / q + 1;
    }
    
    return total;
}

ll bs() {
    ll l = 1, r = 1e18, res = 0;
    
    while (l <= r) {
        ll m = l + (r - l) / 2;
        if (cnt(m) >= x) {
            res = m;
            r = m - 1;
        }
        else l = m + 1;
    }
    return res;
}

void Solve() {
    cin >> n >> x;
    v.resize(n);
    for (int i = 0; i < n; ++i) cin >> v[i].first >> v[i].second;
    
    cout << bs();
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}