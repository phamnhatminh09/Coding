#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int t;
	cin >> t;
	while (t--) {
		long a, b, c;
		cin >> a >> b >> c;
		cout << min({abs(a + b + c), abs(a + b - c), abs(a + b * c), abs(a - b - c), abs(a - b + c), abs(a - b * c), abs(a * b + c), abs(a * b - c), abs(a * b * c)}) << "\n";
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}