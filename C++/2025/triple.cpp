#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
#define sz(x) (x).size()
const int lim = 1e7;
const ll N = 1e5 + 5;

vector<int> prime, lpf;

void sieve(int lim) {
    prime.assign(1, 2);
    lpf.assign(lim + 1, 2);
    
    lpf[1] = 1;
    for (int i = 3; i <= lim; i += 2) {
        if (lpf[i] == 2) prime.push_back(lpf[i] = i);
        for (int j = 0; j < sz(prime) && prime[j] <= lpf[i] && prime[j] * i <= lim; ++j) lpf[prime[j] * i] = prime[j];
    }
}

int getm(int x) {
    int mask = 1;
    
    while (x > 1) {
        int p = lpf[x], f = 0;
        do x /= p, f++; while (p == lpf[x]);
        if (f & 1) mask *= p;
    }
    
    return mask;
}

ll f(int x) {
	return 1LL * x * (x - 1) / 2;
}

ll cal(int n) {
    vector<int> cnt(n + 1, 0);
    ll res = 0;
    for (int a = 1; a <= n; ++a) res += f(cnt[getm(a)]++);

    return res;
}

void Solve() {
	int n;
    cin >> n;
    sieve(n + 500);
    cout << cal(n);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}