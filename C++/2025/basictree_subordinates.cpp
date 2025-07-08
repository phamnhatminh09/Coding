#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void dfs(int u, vector<vector<int>>& tree, vector<int>& node) {
    for (int v : tree[u]) {
        dfs(v, tree, node);
        node[u] += node[v] + 1;
    }
}
void Solve() {
	int n;
	cin >> n;
	
	vector<vector<int>> tree(n + 1);
	for (int i = 2; i <= n; ++i) {
		int x;
		cin >> x;
		tree[x].push_back(i);
	}
	
	
	vector<int> node(n + 1, 0);
	dfs(1, tree, node);
	
	for (int i = 1; i <= n; ++i) cout << node[i] << ' ';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}