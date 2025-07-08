#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll recursion (int n) {
	if (n == 1) return 1;
	return n + recursion(n - 1);
}

void Solve() {
	int n;
	cin >> n;
	cout << recursion(n);
}

int main() {
    faster
    
    Solve();
    
    return 0;
}