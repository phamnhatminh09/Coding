#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<int> adj[N];
bool check[N];
int cnt = 0, res = 0;

bool dfs(int u, int p) {
	bool temp = check[u];
	
	for (int v : adj[u]) {
		if (v == p) continue;
		
		bool c = dfs(v, u);
		
		if (c) {
			res += 2;
			temp = true;
		}
	}
	
	return temp;
}

void Solve() {
	int m, n;
	cin >> n >> m;
	
	for (int i = 0; i < m; ++i) {
		int x;
		cin >> x;
		check[x] = true;
	}
	
	for (int i = 1; i < n; ++i) {
		int u, v;
		cin >> u >> v;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	
	dfs(0, -1);
	
	
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}

/*#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5 + 5;
vector<int> adj[MAXN];
bool check[MAXN];
int cnt[MAXN];
int res = 0;

bool dfs(int u, int p) {
    bool temp = check[u];
    
    for (int v : adj[u]) {
        if (v == p) continue;
        
        bool c = dfs(v, u);
        
        if (c) {
            res += 2;
            temp = true;
        }
    }
    
    return temp;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, m;
    cin >> n >> m;

    for (int i = 0; i < m; ++i) {
        int x;
        cin >> x;
        check[x] = true;
    }

    for (int i = 0; i < n - 1; ++i) {
        int a, b;
        cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    dfs(0, -1);

    int start_node = -1;
    for (int i = 0; i < n; ++i) {
        if (check[i]) {
            start_node = i;
            break;
        }
    }

    if (start_node == -1) {
        cout << "0\n";
        return 0;
    }

    vector<int> dist(n, -1);
    queue<int> q;
    q.push(start_node);
    dist[start_node] = 0;
    int farthest_node = start_node;
    int max_dist = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (check[v] && dist[v] > max_dist) {
                    max_dist = dist[v];
                    farthest_node = v;
                }
            }
        }
    }

    fill(dist.begin(), dist.end(), -1);
    q.push(farthest_node);
    dist[farthest_node] = 0;
    max_dist = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                if (check[v] && dist[v] > max_dist) {
                    max_dist = dist[v];
                }
            }
        }
    }

    res -= max_dist;
    cout << res;

    return 0;
}*/