#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;
typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void gen(int n, int k, string s, int cnt, int pos) {
    if (pos == n) {
        if (cnt == k) {
            for (int i = 0; i < n; i++) {
                cout << s[i];
                if (i < n - 1) cout << " ";
            }
            cout << '\n';
        }
        return;
    }
    
    if (n - pos - 1 >= k - cnt) {
        s[pos] = '0';
        gen(n, k, s, cnt, pos + 1);
    }
    
    if (cnt < k) {
        s[pos] = '1';
        gen(n, k, s, cnt + 1, pos + 1);
    }
}

void Solve() {
	ull n, k;
	cin >> n >> k;
	
	string s(n, ' ');
    gen(n, k, s, 0, 0);
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}