#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll recursion(int n) {
	if (n == 0) return 0;
	return n % 10 + recursion(n / 10);
}

void Solve() {
	int n;
	cin >> n;
	cout << recursion(n) << endl;
}

int main() {
    faster
    
    Solve();
    
    return 0;
}