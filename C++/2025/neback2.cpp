#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void gen(ull n, string s) {
    if (s.length() == n * 2) {
        cout << s << '\n';
        return;
    }
    
    gen(n, s + "0 ");
    gen(n, s + "1 ");
}


void Solve() {
	ull n;
	cin >> n;
	
	gen(n, "");
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}