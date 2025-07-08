#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
#define int long long
const ll N = 1e5 + 5;
int n, k, D, l[100005], q[4], cost[10005][4];

void Solve() {
	cin >> n >> k >> D;
    for (int i = 1; i <= n; i++) cin >> q[i];
    
    for (int i = 0; i < D; i++) {
        for (int j = 1; j <= n; j++) cin >> cost[i][j];
    }
    
    l[0] = k;
    for (int d = 0; d < D - 1; d++) {
        for (int x = 0; x <= q[1]; x++) {
            for (int y = 0; y <= q[2]; y++) {
                int tmp = x * cost[d][1] + y * cost[d][2];
                int z = 0;
                if (tmp <= l[d]) {
                    if (cost[d + 1][3] > cost[d][3]) {
                        z = min((l[d] - tmp) / cost[d][3], q[3]);
                        tmp += cost[d][3] * z;
                    }
                    if (l[d + 1] < l[d] - tmp + x * cost[d + 1][1] + y * cost[d + 1][2] + z * cost[d + 1][3]) l[d + 1] = l[d] - tmp + x * cost[d + 1][1] + y * cost[d + 1][2] + z * cost[d + 1][3];
                }
            }
        }
    }
    
    cout << l[D - 1];
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}