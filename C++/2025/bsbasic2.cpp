#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	map <long, long> mp;
	long n, x;
	cin >> n;
	
	for (long i = 0; i < n; ++i) {
		cin >> x;
		if (mp.find(x)) cout << 1;
		else cout << 0;
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}