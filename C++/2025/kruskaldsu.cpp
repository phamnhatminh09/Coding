#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

vector<int> parent, rank;

void make_set(int v) {
    parent[v] = v;
    rank[v] = 0;
}

int find_set(int v) {
    if (v == parent[v]) return v;
    return parent[v] = find_set(parent[v]);
}

void union_sets(int a, int b) {
    a = find_set(a);
    b = find_set(b);
    
    if (a != b) {
        if (rank[a] < rank[b]) swap(a, b);
        
        parent[b] = a;
        
        if (rank[a] == rank[b]) rank[a]++;
    }
}

struct Edge {
    int u, v, weight;
    bool operator<(Edge const& other) {
        return weight < other.weight;
    }
};

void Solve() {
	int n;
	vector<Edge> edges;
	
	int cost = 0;
	vector<Edge> result;
	parent.resize(n);
	rank.resize(n);
	for (int i = 0; i < n; i++) make_set(i);
	
	sort(edges.begin(), edges.end());
	
	for (Edge e : edges) {
	    if (find_set(e.u) != find_set(e.v)) {
	        cost += e.weight;
	        result.push_back(e);
	        union_sets(e.u, e.v);
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