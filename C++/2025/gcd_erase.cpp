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
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    if (n == 1) {
        cout << a[0] << '\n';
        return;
    }

    vector<int> pref(n);
    pref[0] = a[0];
    for (int i = 1; i < n; ++i) pref[i] = __gcd(pref[i - 1], a[i]);

    vector<int> v(n);
    v[n - 1] = a[n - 1];
    for (int i = n - 2; i >= 0; --i) v[i] = __gcd(v[i + 1], a[i]);

    int res = 1;
    for (int i = 0; i < n; ++i) {
        int x;
        if (i == 0) x = v[i + 1];
        else if (i == n - 1) x = pref[i - 1];
        else x = __gcd(pref[i - 1], v[i + 1]);
        
        if (x > res) res = x;
    }

    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}