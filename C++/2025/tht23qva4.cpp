#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {-
	ll n;
	cin >> n;
	
	ll line = ceil(sqrt(n)), numline = 2 * line - 1;
	ll max = line * line, min = max - numline + 1;
	if (line % 2 != 0) {
		ll pos = max - n + 1;
		cout << pos + line;
	}
	else {
		ll pos = n - min + 1;
		cout << pos + line;
	}
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}