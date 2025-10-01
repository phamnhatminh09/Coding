#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<int>> adj;
vector<int> subtree;
int n, res;

void dfs(int u, int parent) {
    subtree[u] = 1;
    
    for (int v : adj[u]) {
        if (v != parent) {
            dfs(v, u);
            subtree[u] += subtree[v];
        }
    }
}

void centroid(int u, int parent) {
    bool is_res = true;
    for (int v : adj[u]) {
        if (v != parent && subtree[v] > n / 2) {
            is_res = false;
            centroid(v, u);
            break;
        }
    }
    
    if (is_res) res = u;
}

void Solve() {
    cin >> n;
    
    adj.resize(n + 1);
    subtree.resize(n + 1);
    
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    dfs(1, -1);
    centroid(1, -1);
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}