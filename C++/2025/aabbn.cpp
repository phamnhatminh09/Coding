#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("AABBN.INP", "r", stdin);
#define write freopen("AABBN.OUT", "w", stdout);
const ll N = 1e5 + 5;

vector<ll> getdiv(ll n) {
    vector<ll> div;
    if (n < 2) return div;
    
    for (ll i = 2; i * i <= n; ++i) {
        while (n % i == 0) {
            div.push_back(i);
            n /= i;
        }
    }
    
    if (n > 1) div.push_back(n);
    
    return div;
}

ll cntpair(ll n) {
	if (n == 0) return 0;
	
	ll k = sqrt(n);
	
	if (k * k != n) return 0;
	
	vector<ll> div = getdiv(k);
	map<ll, int> m;
	
	int cnt = 0;
	for (ll x : div) {
		if (x % 2 == 0) cnt++;
		m[x]++;
	}
	
	if (cnt < 2) return 0;
	
	ll res = 1;
	for (auto& x : m) {
		if (x.first == 2) continue;
		
		int temp = x.second;
		res *= (temp + 1);
	}
	
	res *= (cnt - 1);
	
	return res;
}

void Solve() {
	ll n;
	cin >> n;
	
	cout << cntpair(n);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}