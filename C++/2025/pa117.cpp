#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n;
	cin >> n;
	cout << n * (n + 1) * (2 * n + 1) / 6;
}

int main() {
    faster
    
    Solve();
    
    return 0;
}
