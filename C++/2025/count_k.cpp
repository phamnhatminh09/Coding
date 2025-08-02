#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m, k;
    cin >> n >> m >> k;
    
    vector<vector<int>> mat(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) cin >> mat[i][j];
    }
    
    vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= m; ++j) prefix[i][j] = prefix[i - 1][j] + prefix[i][j - 1] - prefix[i - 1][j - 1] + (mat[i - 1][j - 1] == k ? 1 : 0);
    }
    
    int q;
    cin >> q;
    while (q--) {
        int x, y, u, v;
        cin >> x >> y >> u >> v;
        int cnt = prefix[u][v] - prefix[x - 1][v] - prefix[u][y - 1] + prefix[x - 1][y - 1];
        cout << cnt << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}