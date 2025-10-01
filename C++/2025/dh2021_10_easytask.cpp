#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void sieve(ll n, vector<bool>& isp) {
    isp[0] = isp[1] = false;
    
    for (ll i = 2; i * i <= n; ++i) {
        if (isp[i]) {
            for (ll j = i * i; j <= n; j += i) isp[j] = false;
        }
    }
}

void Solve() {
	ll n;
    cin >> n;
    vector<ll> a(n);
    for (ll i = 0; i < n; ++i) cin >> a[i];

    vector<bool> isp(n + 1, true);
    sieve(n, isp);

    vector<ll> psum(n + 1, 0);
    for (ll i = 1; i <= n; ++i) psum[i] = psum[i - 1] + a[i - 1];

    ll res = LLONG_MIN;
    vector<ll> primes;
    for (ll i = 2; i <= n; ++i) {
        if (isp[i]) primes.push_back(i);
    }

    for (size_t i = 0; i < primes.size(); ++i) {
        ll l = primes[i];
        for (size_t j = i; j < primes.size(); ++j) {
            ll r = primes[j], x = psum[r] - psum[l - 1];
            if (x > res) res = x;
        }
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