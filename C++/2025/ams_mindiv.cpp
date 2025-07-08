#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	ll x, k;
	cin >> x >> k;
	
	ll d = gcd(x, k);
	
	cout << k / d;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}