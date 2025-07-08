#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int n;
int d[maxN], par[maxN];
bool visit[maxN];
vector <int> g[maxN];

void bfs(int s) {
    fill_n(d, n + 1, 0);
    fill_n(par, n + 1, -1);
    fill_n(visit, n + 1, false);

    queue <int> q;
    q.push(s);
    visit[s] = true;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : g[u]) {
            if (!visit[v]) {
                d[v]     = d[u] + 1;
                par[v]   = u;
                visit[v] = true;
                q.push(v);
            }
        }
    }
}

void Solve() {
	if (!visit[u]) cout << "No path!";
	else {
	    vector <int> path;
	    for (int v = u; v != -1; v = par[v])
	        path.push_back(v);
	    reverse(path.begin(), path.end());
	
	    cout << "Path: ";
	    for (auto v : path) cout << v << ' ';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}