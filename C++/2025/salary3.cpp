#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<int> adj[N];
int in[N], out[N], f[N], n, q, t = 0;
ll sal[N], fenwick[N];

void dfs(int u) {
	in[u] = ++t;
	f[t] = u;
	
	for (int v : adj[u]) dfs(v);
	
	out[u] = t;
}

void update(int index, ll val) {
	while (index <= n) {
		fenwick[index] += val;
		index += index & -index;
	}
}

ll cal(int x) {
	ll res = 0;
	
	while (x > 0) {
		res += fenwick[x];
		x -= x & -x;
	}
	
	return res;
}

void Solve() {
	cin >> n >> q;
	int root = 0;
	
	for (int i = 1; i <= n; ++i) {
		int p;
		cin >> p;
		
		if (p == 0) root = i;
		else adj[p].push_back(i);
	}
	
	dfs(root);
	
	for (int i = 1; i <= n; ++i) {
		cin >> sal[i];
		update(in[i], sal[i]);
	}
	
	while (q--) {
		int type, x;
		cin >> type >> x;
		
		if (type == 1) {
			ll v;
			cin >> v;
			
			update(in[x], v);
			sal[x] += v;
		}
		else {
			ll sum = cal(out[x]) - cal(in[x] - 1);
			cout << sum << '\n';
		}
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}