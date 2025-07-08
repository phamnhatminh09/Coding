#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
using pii = pair<int, int>;
const ll mod = 123456789;

int m;

vector<ll> v(const vector<ll>& x, const vector<ll>& y) {
	vector<ll> z(m,0);
    for(int i = 0; i < m; i++) if(x[i])
        for(int j = 0; j < m; j++) {
            z[(i + j) % m] = (z[(i + j) % m] + x[i] * y[j]) % mod;
        }
    return z;
}

void Solve() {
    ll n, k;
    cin >> n >> k >> m;
    ll m1 = (k + 1) / 2, m2 = k / 2;
    int g = gcd(2, m), p = m / g;
    vector<ll> box1(m, 0), box2(m, 0);
    
    for(int i = 0; i < p; i++){
        int r1 = (1 + 2LL * i) % m, r2 = (2 + 2LL * i) % m;
        box1[r1]++;
        box2[r2]++;
    }
    
    vector<ll> a(m,0), b(m,0);
    ll f1 = m1 / p, r1 = m1 % p;
    ll f2 = m2 / p, r2 = m2 % p;
    
    for(int r = 0; r < m; r++){
        a[r] = (box1[r] * f1) % mod;
        b[r] = (box2[r] * f2) % mod;
    }
    
    for(int i = 0; i < r1; i++) a[(1 + 2LL * i) % m] = (a[(1 + 2LL * i) % m] + 1) % mod;
    for(int i = 0; i < r2; i++) b[(2 + 2LL * i) % m] = (b[(2 + 2LL * i) % m] + 1) % mod;
    
    vector<ll> c = v(a, b);
    ll t = n / 2;
    vector<ll> res(m, 0);
    res[0] = 1;
    vector<ll> bs = c;
    
    while(t) {
        if(t & 1) res = v(res, bs);
        bs = v(bs, bs);
        t >>= 1;
    }
    
    if(n & 1) res = v(res, a);
    cout << res[0];
}

int main(){
	//read
	//write
	faster
	
	Solve();
	
    return 0;
}