#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
vector<int> a;

int bs(int l, int r, int x) {
    int res = -1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        if (a[m] > x) {
            res = m;
            r = m - 1;
        }
        else l = m + 1;
    }
    return res;
}

void Solve() {
    int n, t;
    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    cin >> t;
    vector<int> q(t);
    for (int i = 0; i < t; ++i) cin >> q[i];

    for (int i = 0; i < t; ++i) {
        int x = q[i], pos = bs(0, n - 1, x);
        if (pos != -1) cout << a[pos] << " ";
     	else cout << -1 << " ";
    }
}

int main() {
    faster
    
    Solve();
    
    return 0;
}