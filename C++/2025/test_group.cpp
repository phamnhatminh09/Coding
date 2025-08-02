#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    sort(a.begin(), a.end());

    ll res = 0, l = 0, r = n - 1;

    while (k--) {
        ll x = (ll)a[r] * a[r - 1] * a[r - 2], y = (ll)a[l] * a[l + 1] * a[r];

        if (x > y) {
            res += x;
            r -= 3;
        }
        else {
            res += y;
            l += 2;
            r -= 1;
        }
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