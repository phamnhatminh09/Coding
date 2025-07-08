#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

const long long INF = 2000000000000000000LL;
struct Edge{
    int v;
    long long w;
};

void dijkstra(int n, int S, vector<vector<Edge>> E,
              vector<long long> &D, vector<int> &trace) {
    D.resize(n, INF);
    trace.resize(n, -1);

    vector<bool> P(n, 0);
    D[S] = 0;

    for (int i = 0; i < n; i++) {
        int uBest; // tìm đỉnh u chưa dùng, có khoảng cách nhỏ nhất
        long long Max = INF;
        for (int u = 0; u < n; u++) {
            if(D[u] < Max && P[u] == false) {
                uBest = u;
                Max = D[u];
            }
        }

        // cải tiến các đường đi qua u
        int u = uBest;
        P[u] = true;
        for(auto x : E[u]) {
            int v = x.v;
            long long w = x.w;
            if(D[v] > D[u] + w) {
                D[v] = D[u] + w;
                trace[v] = u;
            }
        }
    }
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