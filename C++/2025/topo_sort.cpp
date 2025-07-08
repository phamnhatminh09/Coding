#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int n, m, s;
vector<vector<pair <int, int> > > adj;
vector <int> topo, trace, topoId;
vector <long long> d;
vector <bool> visit;

void dfs(int u) {
    visit[u] = 1;
    for (auto p : adj[u]) {
        auto v = p.first;
        if (!visit[v]) {
            dfs(v);
        }
    }
    topo.push_back(u);
}

long long spDAG() {
    for (int u = 0; u < n; u++) {
        if (!visit[u]) {
            dfs(u);
        }
    }
    reverse(topo.begin(), topo.end());
    for (int i = 0; i < n; i++) {
        topoId[topo[i]] = i;
    }

    fill(d.begin(), d.end(), INF);
    d[s] = 0;
    for (int i = topoId[s]; i < n; i++) {
        int u = topo[i];
        for (auto p : adj[u]) {
            int v = p.first;
            int w = p.second;
            if (d[v] > d[u] + w) {
                d[v] = d[u] + w;
                trace[v] = u;
            }
        }
    }
    return *min_element(d.begin(), d.end());
}

vector<int> path() {
    vector<int> ret;
    if (d[t] != INF) {
        return ret;
    }
    int u = t;
    while (u != s) {
        ret.push_back(u);
        u = trace[u];
    }
    ret.push_back(u);
    reverse(ret.begin(), ret.end());
    return ret;
}

void Solve() {
	
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}