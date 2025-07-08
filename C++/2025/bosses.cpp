#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<int>> adj;
vector<int> sal;

void dfs(int u) {
    sal[u] = 1;
    
    for (int v : adj[u]) {
        dfs(v);
        sal[u] += sal[v];
    }
}

void Solve() {
	int n;
    cin >> n;

    adj.resize(n + 1);
    vector<vector<int>> v(n + 1);

    for (int i = 1; i <= n; ++i) {
        int k;
        cin >> k;
        v[i].resize(k);
        for (int j = 0; j < k; ++j) cin >> v[i][j];
    }
    
    int root = -1;
    for (int i = 1; i <= n; ++i) {
        if (v[i].empty()) {
            root = i;
            break;
        }
    }
    
    if (root == -1) root = 1;
    
    for (int i = 1; i <= n; ++i) {
        if (i == root) continue;
        if (!v[i].empty()) adj[v[i][0]].push_back(i);
    }

    sal.resize(n + 1);
    dfs(root);

    int res = 0;
    for (int i = 1; i <= n; ++i) res += sal[i];

    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}