#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const int N  = 1e5 + 7;

int n, m, cnt = 0;
bool check[N];
vector <int> g[N];

void bfs(int s) {
    ++cnt;
    
    queue <int> q;
    q.push(s);
    check[s] = true;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (auto v : g[u]) {
            if (!check[v]) {
                check[v] = true;
                q.push(v);
            }
        }
    }
}

void Solve() {
    cin >> n >> m;
    
    while (m--) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    fill_n(check, n + 1, false);
    for (int i = 1; i <= n; ++i){
        if (!check[i]) bfs(i);
    }
    
    cout << cnt;
}

int main() {
	//read
	//write
    faster
    
	Solve();
    
    return 0;
}