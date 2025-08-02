#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

const int MAX = 1e6 + 5;
vector<bool> check(MAX, true);
vector<int> pr;

void sieve() {
    check[0] = check[1] = false;
    
    for (int i = 2; i * i < MAX; ++i) {
        if (check[i]) {
            for (int j = i * i; j < MAX; j += i) check[j] = false;
        }
    }
    
    for (int i = 2; i < MAX; ++i) {
        if (check[i]) pr.push_back(i);
    }
}

bool isp(ll n) {
    if (n < 2) return false;
    
    for (int p : pr) {
        if (p * p > n) break;
        if (n % p == 0) return false;
    }
    
    return true;
}

int cntdiv(ll n) {
    int div = 1;
    for (int p : pr) {
        if (p * p > n) break;
        int expo = 0;
        while (n % p == 0) {
            n /= p;
            expo++;
        }
        div *= (expo + 1);
    }
    
    if (n > 1) div *= 2;
    return div;
}

void Solve() {
	sieve();

    int t;
    cin >> t;
    while (t--) {
        ll a, b;
        cin >> a >> b;
        int cnt = 0;
        
        for (ll n = a; n <= b; ++n) {
            int d = cntdiv(n);
            if (isp(d)) cnt++;
        }
        
        cout << cnt << '\n';
    }
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}