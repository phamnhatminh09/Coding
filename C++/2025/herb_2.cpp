#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int n, q, a[N], f[N], b[N], pr[N];
vector<int> primes[N];

void sieve() {
    for (int i = 2; i < N; ++i) {
        if (primes[i].empty()) {
            for (int j = i; j < N; j += i)
                primes[j].push_back(i);
        }
    }
}

void Solve() {
	cin >> n >> q;
    for (int i = 1; i <= n; ++i) cin >> a[i];

    sieve();
    
    fill(b, b + N, 0);

    int l = 0;
    for (int i = 1; i <= n; ++i) {
        for (int p : primes[a[i]]) {
            l = max(l, b[p]);
            b[p] = i;
        }
        
        pr[i] = l;
    }

    f[0] = 0;
    for (int i = 1; i <= n; ++i) f[i] = f[pr[i]] + 1;

    while (q--) {
        int l, r;
        cin >> l >> r;
        
        int res = 0, pos = r;
        
        while (pos >= l) {
            res++;
            pos = pr[pos];
            if (pos < l) break;
        }
        
        cout << res << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}