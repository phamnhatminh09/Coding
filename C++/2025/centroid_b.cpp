#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const int MAXN = 2e5 + 5;

vector<int> adj[MAXN];
bool visited[MAXN];
int subtree[MAXN], n, k1, k2;
ll res = 0;

void dfs(int u, int par) {
    subtree[u] = 1;
    
    for (int v : adj[u]) {
        if (v != par && !visited[v]) {
            dfs(v, u);
            subtree[u] += subtree[v];
        }
    }
}

int cfind(int u, int par, int total) {
    for (int v : adj[u]) {
        if (v != par && !visited[v] && subtree[v] > total / 2) return cfind(v, u, total);
    }
    
    return u;
}

void count_paths(int u, int par, int x, vector<int>& depth) {
    if (x > k2) return;
    depth.push_back(x);
    for (int v : adj[u]) {
        if (v != par && !visited[v]) {
            count_paths(v, u, x + 1, depth);
        }
    }
}

void centroid(int x) {
    vector<int> v1;
    v1.push_back(0);

    for (int v : adj[x]) {
        if (!visited[v]) {
            vector<int> depth;
            count_paths(v, x, 1, depth);
            sort(depth.begin(), depth.end());
            
            for (int d : depth) {
                int lower = max(0, k1 - d), upper = k2 - d;
                
                if (upper < 0) continue;
                auto l = lower_bound(v1.begin(), v1.end(), lower), r = upper_bound(v1.begin(), v1.end(), upper);
                
                res += (r - l);
            }

            v1.insert(v1.end(), depth.begin(), depth.end());
            sort(v1.begin(), v1.end());
        }
    }
}

void decomposition(int u) {
    dfs(u, -1);
    int x = cfind(u, -1, subtree[u]);
    visited[x] = true;
    centroid(x);

    for (int v : adj[x]) {
        if (!visited[v]) {
            decomposition(v);
        }
    }
}

void Solve() {
	cin >> n >> k1 >> k2;
    
    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }
    
    decomposition(1);
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}