#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const ll oo = 1e18;

void Solve() {
	int n;
	cin >> n;
	
	ll sum = 0, total = 0;
	for (int i = 1; i <= n; ++i) total += i;
	for (int i = 1; i <= n - 1; ++i) {
		ll x;
		cin >> x;
		sum += x;
	}
	
	cout << total - sum;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}