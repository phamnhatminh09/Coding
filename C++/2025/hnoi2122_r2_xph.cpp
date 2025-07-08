#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

void Solve() {
	int n, m;
    cin >> n >> m;
    vector<pair<int, int>> v(n);
    vector<int> l(n), r(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i].first >> v[i].second;
        l[i] = v[i].first;
        r[i] = v[i].second;
    }
    
    sort(l.begin(), l.end());
    sort(r.begin(), r.end());

    vector<int> cnt(n);
    for (int i = 0; i < n; ++i) {
        int x = v[i].first, y = v[i].second, lcnt = upper_bound(l.begin(), l.end(), y) - l.begin(), rcnt = lower_bound(r.begin(), r.end(), x) - r.begin();
        cnt[i] = lcnt - rcnt - 1;
    }

    for (int i = 0; i < n; ++i) cout << cnt[i] << '\n';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}