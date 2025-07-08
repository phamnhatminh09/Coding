#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int x;
	cin >> x;
	
	int neg_y = -2023 - x, pos_y = 2023 - x;
	if (x - neg_y < x - pos_y) cout << x - neg_y;
	else cout << x - pos_y;
}

int main() {
    faster
    
    Solve();
    
    return 0;
}