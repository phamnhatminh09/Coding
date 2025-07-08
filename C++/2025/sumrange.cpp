#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n;
    cin >> n;
    
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];
    
    vector<ll> v1(n + 1, 0), v2(n + 1, 0);
    for (int i = 1; i <= n; ++i) v1[i] = v1[i - 1] + a[i];
    for (int i = 1; i <= n; ++i) v2[i] = v2[i - 1] + b[i];
    
    vector<vector<ll>> sum(n + 1, vector<ll>(n + 1, 0));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (i <= j) sum[i][j] = v1[j] - v1[i - 1];
            else sum[i][j] = v2[i] - v2[j - 1];
        }
    }
    
    ll res = LLONG_MIN;
    for (int x = 1; x <= n; ++x) {
        for (int y = x; y <= n; ++y) {
            for (int c = 1; c <= n; ++c) {
                for (int d = c; d <= n; ++d) {
                    ll curr = 0;
                    for (int i = x; i <= y; ++i) {
                        for (int j = c; j <= d; ++j) curr += sum[i][j];
                    }
                    
                    if (curr > res)  res = curr;
                }
            }
        }
    }
    
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}