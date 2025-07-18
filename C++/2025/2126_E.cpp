#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        
        vector<int> p(n + 2), s(n + 2);
        for (int i = 1; i <= n; ++i) cin >> p[i];
        for (int i = 1; i <= n; ++i) cin >> s[i];

        p[0] = s[n + 1] = 0;

        bool ok = true;
        for (int i = 1; i <= n; ++i) {
            int g = __gcd(p[i], s[i]);
            if (g != __gcd(p[i - 1], s[i]) || g != __gcd(p[i], s[i + 1])) {
                ok = false;
                break;
            }
        }
        
        cout << (ok ? "YES\n" : "NO\n");
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}