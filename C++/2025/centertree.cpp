#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<vector<int>> adj;
vector<int> par;

pair<int, int> bfs(int x) {
    int n = adj.size();
    vector<int> dist(n, -1);
    queue<int> q;
    
    q.push(x);
    dist[x] = 0;
    int temp = x;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                
                if (dist[v] > dist[temp]) temp = v;
            }
        }
    }
    
    return {temp, dist[temp]};
}

vector<int> find_center() {
    int n = adj.size(), u = bfs(0).first, v = bfs(u).first, d = bfs(u).second;
    
    vector<int> path;
    par.assign(n, -1);
    queue<int> q;
    q.push(u);
    par[u] = u;
    
    while (!q.empty()) {
        int curr = q.front();
        q.pop();
        for (int x : adj[curr]) {
            if (par[x] == -1) {
                par[x] = curr;
                q.push(x);
            }
        }
    }
    
    while (v != u) {
        path.push_back(v);
        v = par[v];
    }
    
    path.push_back(u);
    
    vector<int> center;
    if (d % 2 == 0) center.push_back(path[d / 2]);
    else {
        center.push_back(path[d / 2]);
        center.push_back(path[d / 2 + 1]);
    }
    
    sort(center.begin(), center.end());
    return center;
}

void Solve() {
    int n;
    cin >> n;
    adj.resize(n);
    
    for (int i = 0; i < n - 1; ++i) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    vector<int> center = find_center();
    int r = (bfs(bfs(0).first).second + 1) / 2;
    
    cout << r << " " << center.size() << "\n";
    for (int node : center) cout << node + 1 << " ";
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}