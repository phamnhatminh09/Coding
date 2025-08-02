#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int a, n;
	cin >> a >> n;
	
	a %= 10;
	if (n % 4 == 0) n = 4;
	else n %= 4;
	cout << (int) pow(a, n) % 10;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}