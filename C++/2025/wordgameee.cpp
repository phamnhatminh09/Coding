#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll modn(ll x, ll n) {
	return (x % n + n) % n;
}

void Solve() {
	string s;
	int k, x;
	
	cin >> s >> k >> x;
	
	ll n = s.size();
	k = modn(k, n) * modn(k + 1, n) / 2 % n;
	
	rotate(s.begin(), s.begin() + k, s.end());
	cout << s[x - 1];
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}