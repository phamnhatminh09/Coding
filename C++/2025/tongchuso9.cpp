#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll mod9(ll x) {
	return (x % 9 + 9) % 9;
}

void Solve() {
	ll a, b;
	cin >> a >> b;
	
	ll sumb = mod9(b) * mod9(b + 1) / 2 % 9, suma = mod9(a - 1) * mod9(a) / 2 % 9;
	cout << (sumb - suma + 9) % 9;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}