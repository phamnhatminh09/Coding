#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<ll> getdiv(ll n) {
	vector<ll> div;
	for (ll i = 1; i <= sqrt(n); ++i) {
		if (n % i == 0) {
			div.push_back(i);
			if (i != n / i) div.push_back(n / i);
		}
	}
	
	return div;
}

void Solve() {
	ll n;
	cin >> n;
	
	ll cnt = 0, n2 = 2 * n;
	
	vector<ll> div = getdiv(n2);
	
	for (ll k : div) {
		ll x = n2 / k - (k - 1);
		if (x > 0 && x % 2 == 0) {
			if (x / 2 > 0) cnt++;
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