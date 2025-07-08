#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int n, m;
vector<pair<int, int>> e;
vector<int> p;

int fset(int u) {
    if (p[u] == u) return u;
    return p[u] = fset(p[u]);
}

void uset(int u, int v) {
    u = fset(u);
    v = fset(v);
    if (u != v) p[v] = u;
}

bool check(const vector<bool>& select) {
    p.resize(n + 1);
    
    for (int i = 1; i <= n; i++) p[i] = i;
    
    for (int i = 0; i < m; i++) {
        if (select[i]) {
            int u = e[i].first;
            int v = e[i].second;
            uset(u, v);
        }
    }
    
    int root = fset(1);
    for (int i = 2; i <= n; i++) {
        if (fset(i) != root) return false;
    }
    
    return true;
}

int cnt() {
    int total = 0;
    
    for (int mask = 1; mask < (1 << m); mask++) {
        vector<bool> select(m, false);
        for (int i = 0; i < m; i++) {
            if (mask & (1 << i)) select[i] = true;
        }
        
        if (check(select)) total++;
    }
    
    return total;
}

void Solve() {
    cin >> n >> m;
    e.resize(m);
    for (int i = 0; i < m; i++) cin >> e[i].first >> e[i].second;
    
    cout << cnt();
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}