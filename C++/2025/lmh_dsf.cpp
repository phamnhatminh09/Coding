#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;
const int MAX = 1e6 + 5;
int p[MAX];
int r[MAX];

void makeSet(int n) {
    for (int i = 1; i <= n; i++) {
        p[i] = i;
        r[i] = 0;
    }
}

int find(int u) {
    if (p[u] != u) p[u] = find(p[u]);
    return p[u];
}

bool unionSets(int u, int v) {
    int U = find(u);
    int V = find(v);
    
    if (U == V) return false;
    
    if (r[U] > r[V]) p[V] = U;
    else if (r[U] < r[V]) p[U] = V;
    else {
        p[V] = U;
        r[U]++;
    }
    
    return true;
}

void Solve() {
	int n, m;
    cin >> n >> m;
    
    makeSet(n);
    
    while (m--) {
        int u, v;
        cin >> u >> v;
        
        if (unionSets(u, v)) cout << "Y\n";
        else cout << "N\n";
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}