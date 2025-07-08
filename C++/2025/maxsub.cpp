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

    ll res = a[0], x = a[0];

    for (int i = 1; i < n; ++i) {
        x = max((ll)a[i], x + a[i]);
        res = max(res, x);
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