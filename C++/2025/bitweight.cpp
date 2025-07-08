#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5, mod = 1e9 + 7, phi = mod - 1;

ll lmod(const string& s, ll lmod) {
    ll res = 0;
    
    for (char ch : s) res = (res * 10 + (ch - '0')) % lmod;
    
    return res;
}

void Solve() {
	ll t;
    cin >> t;
    cin.ignore();
    
    while (t--) {
        string s;
        getline(cin, s);
        
        ll nmod = lmod(s, phi), x = (nmod - 1 + phi) % phi, temp = 1, base = 2;
        
        while (x > 0) {
            if (x % 2 == 1) temp = (temp * base) % mod;
            base = (base * base) % mod;
            x /= 2;
        }
        
        ll n_mod = lmod(s, mod);
        ll res = (n_mod * temp) % mod;
        cout << res << '\n';
    }
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}