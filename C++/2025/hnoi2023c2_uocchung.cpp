#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("UOCCHUNG.INP", "r", stdin);
#define write freopen("UOCCHUNG.OUT", "w", stdout);
const ll N = 1e5 + 5;

vector<ll> getdiv(ll n) {
	vector<ll> div;
	
	for (ll i = 1; i * i <= n; ++i) {
		if (n % i == 0) {
			div.push_back(i);
			if (i != n / i) div.push_back(n / i);
		}
	}
	
	return div;
}

void Solve() {
	ll a, b;
	cin >> a >> b;
	
	ll g = __gcd(a, b);
	vector<ll> div = getdiv(g);
	
	sort(div.begin(), div.end(), greater<ll>());
	if (div.size() >= 2) cout << div[1];
	else cout << -1;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}