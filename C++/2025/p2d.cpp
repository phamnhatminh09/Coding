#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m, q;
    cin >> n >> m >> q;

    vector<vector<int>> a(n + 1, vector<int>(m + 1, 0));
    vector<vector<ll>> pre(n + 1, vector<ll>(m + 1, 0));

    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) {
            cin >> a[i][j];
        }
    }
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) pre[i][j] = a[i][j] + pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
    }

    while (q--) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;

        ll sum = pre[u][v] - pre[x - 1][v] - pre[u][y - 1] + pre[x - 1][y - 1];
        cout << sum << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}