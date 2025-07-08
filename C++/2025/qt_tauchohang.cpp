#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
//const ll N = 1e5 + 5;
const ll MOD1 = 1e9 + 5;
const ll MOD2 = 1e9 + 7;
const ll MOD3 = 1e9 + 9;

ll pow(ll a, ll b, ll mod) {
    ll res = 1;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) {
            res = (res * a) % mod;
        }
        a = (a * a) % mod;
        b /= 2;
    }
    return res;
}

ll inv(ll a, ll mod) {
    return pow(a, mod - 2, mod);
}

ll cal(ll n, ll mod) {
    if (n == 0) return 0;
    ll inv6 = inv(6, mod);
    ll a = n % mod;
    ll b = (n + 1) % mod;
    ll c = (n + 2) % mod;
    ll product = (a * b) % mod;
    product = (product * c) % mod;
    return (product * inv6) % mod;
}

void Solve() {
    ll n;
    cin >> n;
    ll m1 = cal(n, MOD1);
    ll m2 = cal(n, MOD2);
    ll m3 = cal(n, MOD3);
    cout << m1 << " " << m2 << " " << m3;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}