#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void gen(int n, int k, string s, int cnt) {
    if (s.length() == n * 2) {
        if (cnt <= k) cout << s << '\n';
        return;
    }
    
    gen(n, k, s + "0 ", cnt);
    if (cnt < k) gen(n, k, s + "1 ", cnt + 1);
}

void Solve() {
	ull n, k;
	cin >> n >> k;
	
	gen(n, k, "", 0);
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}