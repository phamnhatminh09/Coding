#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int prime(int n) {
    if (n % 2 == 0) return 2;
    
    for (int i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return i;
    }
    
    return n;
}

void Solve() {
	int n;
	cin >> n;
	
	vector<int> a(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	
	int gcd = a[0];
	for (int i = 1; i <= n; ++i) {
		gcd = __gcd(gcd, a[i]);
		if (gcd == 1) break;
	}
	
	if (gcd == 1) cout << -1;
	else cout << prime(gcd);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}