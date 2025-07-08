#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int x, y, z;
	cin >> x >> y >> z;
	
	long temp = x * z;
	if (temp % y == 0) cout << x * z / y - z;
	else cout << x * z / y - z + 1;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}