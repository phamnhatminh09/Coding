#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
#define int long long
const ll N = 2e5 + 5;

vector<int> adj[N];
int dista[N], distb[N];

pair<int, int> bfs(int st, int n) {
    vector<int> dist(n + 1, -1);
    queue<int> q;
    int far = st, maxx = 0;
    
    q.push(st);
    dist[st] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v : adj[u]) {
            if (dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
                
                if (dist[v] > maxx) {
                    maxx = dist[v];
                    far = v;
                }
            }
        }
    }
    
    return {far, maxx};
}

void cal(int st, int* dist, int n) {
	fill (dist, dist + n + 1, -1);
	queue<int> q;
	
	q.push(st);
	dist[st] = 0;
	
	while (!q.empty()) {
		int u = q.front();
		q.pop();
		
		for (int v : adj[u]) {
			if (dist[v] == -1) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
}

void Solve() {
	int n;
	cin >> n;
	
	for (int i = 0; i < n; ++i) {
		int x, y;
		cin >> x >> y;
		adj[x].push_back(y);
		adj[y].push_back(x);
	}	
	
	pair<int, int> resa = bfs(1, n);
	int a = resa.first;
	
	pair<int, int> resb = bfs(a, n);
	int b = resb.first;
	
	fill(dista, dista + n + 1, -1);
	fill(distb, distb + n + 1, -1);
	cal(a, dista, n);
	cal(b, distb, n);
	
	for (int i = 1; i <= n; ++i) cout << max(dista[i], distb[i]) << ' ';
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}