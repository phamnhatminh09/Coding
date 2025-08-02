#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("CATHINH.INP", "r", stdin);
#define write freopen("CATHINH.OUT", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	ll n, m, k;
	cin >> m >> n >> k;
	
	ll a = m / k, b = n / k;
	cout << m * n - (k * k * a * b);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}