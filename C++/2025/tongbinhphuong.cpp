#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	ll n;
	cin >> n;
	
	ll x = n / 10, y = n % 10, a[10] = {1, 4, 9, 6, 5, 6, 9, 4, 1, 0};
	
	ll sum = x * 45;
	for (ll i = 0; i < y; ++i) sum += a[i];
	
	cout << sum;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}