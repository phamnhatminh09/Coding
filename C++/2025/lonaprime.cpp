#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<ll> sieve(ll limit) {
    vector<bool> isp(limit + 1, true);
    isp[0] = isp[1] = false;
    for (ll i = 2; i * i <= limit; ++i) {
        if (isp[i]) {
            for (ll j = i * i; j <= limit; j += i) {
                isp[j] = false;
            }
        }
    }
    vector<ll> pr;
    for (ll i = 2; i <= limit; ++i) {
        if (isp[i]) {
            pr.push_back(i);
        }
    }
    return pr;
}

void Solve() {
    ll n;
    cin >> n;

    ll cube = cbrt(n);
    vector<ll> pr = sieve(cube);

    int cnt = 0;
    for (int i = 0; i < pr.size(); ++i) {
        for (int j = i + 1; j < pr.size(); ++j) {
            ll p = pr[i], q = pr[j];
            if (p * q > cube) break;
            
            ll s = p * p * p * q * q * q;
            if (s <= n) ++cnt;
        }
    }

    cout << cnt;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}