#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const int base = 31;
const int mod = 1e9 + 7;
const int maxn = 1e6 + 5;

ll powb[maxn];
ll phash[maxn];

void prep_pow(int n) {
    powb[0] = 1;
    for (int i = 1; i <= n; ++i) {
        powb[i] = (powb[i-1] * base) % mod;
    }
}

void prep_hash(const string &s, int n) {
    phash[0] = 0;
    for (int i = 1; i <= n; ++i) {
        phash[i] = (phash[i - 1] * base + (s[i - 1] - 'a' + 1)) % mod;
    }
}

ll hashV(int l, int r) {
    ll val = (phash[r] - phash[l - 1] * powb[r - l + 1] % mod + mod) % mod;
    return val;
}

void Solve() {
	int n, q;
    cin >> n >> q;
    string s;
    cin >> s;

    prep_pow(n);
    prep_hash(s, n);

    while (q--) {
        int x, y, z, t;
        cin >> x >> y >> z >> t;

        int len1 = y - x + 1, len2 = t - z + 1;

        if (len1 != len2) {
            cout << "NO\n";
            continue;
        }

        ll hash1 = hashV(x, y), hash2 = hashV(z, t);

        if (hash1 == hash2) cout << "YES\n";
        else cout << "NO\n";
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}