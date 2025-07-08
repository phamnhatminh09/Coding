#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {string s;
    cin >> s;
    int n = s.size();
    
    vector<int> u(n + 1, 0);
    for (int i = 1; i <= n; ++i) u[i] = u[i - 1] + (s[i - 1] == '(' ? 1 : -1);
    
    vector<int> v(n + 1, 0), t(n + 1, 0);
    t[0] = 0;
    for (int i = 1; i <= n; ++i) t[i] = min(t[i - 1], u[i]);
    
    int q;
    cin >> q;
    while (q--) {
        int l, r;
        cin >> l >> r;
        
        if ((r - l + 1) % 2 != 0) {
            cout << "NO\n";
            continue;
        }
        
        if (u[r] != u[l - 1]) {
            cout << "NO\n";
            continue;
        }
        
        if (t[r] < u[l - 1]) cout << "NO\n";
        else cout << "YES\n";
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}