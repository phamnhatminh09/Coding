#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

void Solve() {
	int n;
    cin >> n;
    vector<ll> a(n);
    ll sum = 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
    }

    ll pre = 0, res = LLONG_MAX;
    for (int i = 0; i < n; ++i) {
        pre += a[i];
        ll diff = abs(2 * pre - sum);
        res = min(res, diff);
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