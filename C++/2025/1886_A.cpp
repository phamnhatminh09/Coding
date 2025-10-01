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
		
		if (n <= 5) {
			cout << "NO\n";
			continue;
		}
		
		int x = 1, y = 2, z = n - 3;
		if (z > y && z % 3 != 0) {
			cout << "YES\n" << x << ' ' << y << ' ' << z << '\n';
			continue;
		}
		
		x = 1, y = 4, z = n - 5;
		if (z > y && z % 3 != 0) {
			cout << "YES\n" << x << ' ' << y << ' ' << z << '\n';
			continue;
		}
		
		x = 2, y = 4, z = n - 6;
		if (z > y && z % 3 != 0) {
			cout << "YES\n" << x << ' ' << y << ' ' << z << '\n';
			continue;
		}
		
		cout << "NO\n";
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}