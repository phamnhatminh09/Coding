#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("stock.inp", "r", stdin);
#define write freopen("stock.out", "w", stdout);
const ll N = 1e5 + 5;

ll l[101][101][101];
ll q[4];
vector<vector<ll>> cost;
ll n, m, t;

void Solve() {
    cin >> n >> m >> t;
    
    for (int i = 1; i <= n; i++) cin >> q[i];
    
    cost.resize(t + 1, vector<ll>(4));
    for (int i = 1; i <= t; i++) {
        for (int j = 1; j <= n; j++) cin >> cost[i][j];
    }
    
    for (int i = n + 1; i <= 3; i++) q[i] = 0;
    
    n = 3;
    
    memset(l, -1, sizeof(l));
    l[0][0][0] = m;
    
    for (int k = 1; k <= t; k++) {
        for (int i1 = q[1]; i1 >= 0; i1--) {
            for (int i2 = q[2]; i2 >= 0; i2--) {
                for (int i3 = q[3]; i3 >= 0; i3--) {
                    ll money = l[i1][i2][i3];
                    if (money > -1) {
                        if (i1 > 0) l[i1 - 1][i2][i3] = max(l[i1 - 1][i2][i3], money + cost[k][1] - 1);
                        if (i2 > 0) l[i1][i2 - 1][i3] = max(l[i1][i2 - 1][i3], money + cost[k][2] - 1);
                        if (i3 > 0) l[i1][i2][i3 - 1] = max(l[i1][i2][i3 - 1], money + cost[k][3] - 1);
                    }
                }
            }
        }
        
        for (int i1 = 0; i1 <= q[1]; i1++) {
            for (int i2 = 0; i2 <= q[2]; i2++) {
                for (int i3 = 0; i3 <= q[3]; i3++) {
                    ll money = l[i1][i2][i3];
                    if (money > -1) {
                        if (i1 < q[1] && money >= cost[k][1] + 1) l[i1 + 1][i2][i3] = max(l[i1 + 1][i2][i3], money - cost[k][1] - 1);
                        if (i2 < q[2] && money >= cost[k][2] + 1) l[i1][i2 + 1][i3] = max(l[i1][i2 + 1][i3], money - cost[k][2] - 1);
                        if (i3 < q[3] && money >= cost[k][3] + 1) l[i1][i2][i3 + 1] = max(l[i1][i2][i3 + 1], money - cost[k][3] - 1);
                    }
                }
            }
        }
    }
    
    cout << l[0][0][0];
}

int main() {
    //read
    //write
    faster
    
    Solve();
    
    return 0;
}