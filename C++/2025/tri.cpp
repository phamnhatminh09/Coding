#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(int n, int m, vector<vector<int>>& adj) {
    if (m != n - 1) return false;

    vector<bool> vs(n + 1, false);
    queue<int> q;
    q.push(1);
    vs[1] = true;
    int count = 1;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (int v : adj[u]) {
            if (!vs[v]) {
                vs[v] = true;
                q.push(v);
                count++;
            }
        }
    }

    return count == n;
}

void Solve() {
	int n, m;
    cin >> n >> m;

    vector<vector<int>> adj(n + 1);

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    if (check(n, m, adj)) cout << "Yes";
    else cout << "No";
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}