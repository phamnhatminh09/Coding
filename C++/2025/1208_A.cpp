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
	int t;
	cin >> t;
	
	while (t--) {
		int a, b, n;
		cin >> a >> b >> n;
		
		int res = 0;
		if (n % 3 == 0) res = a;
		else if (n % 3 == 1) res = b;
		else res = a ^ b;
		
		cout << res << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}