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
		int n;
		cin >> n;
		
		vector<int> a(n), b(n);
		for (int i = 0; i < n; ++i) cin >> a[i];
		for (int i = 0; i < n; ++i) cin >> b[i];
		
		if (b[n - 1] != a[n - 1]) {
			cout << "NO\n";
			continue;
		}
		
		bool check = true;
		for (int i = n - 2; i >= 0; --i) {
			ll p1 = a[i], p2 = a[i] ^ a[i + 1], p3 = a[i] ^ b[i + 1];
			
			if (b[i] != p1 && b[i] != p2 && b[i] != p3) {
				check = false;
				break;
			}
		}
		
		if (check) cout << "YES\n";
		else cout << "NO\n";
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}