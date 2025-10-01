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
	
	if (n == 1) cout << 1;
	else if (n <= 3) cout << "NO SOLUTION";
	else {
		for (int i = 2; i <= n; i += 2) cout << i << ' ';
		for (int i = 1; i <= n; i += 2) cout << i << ' ';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}