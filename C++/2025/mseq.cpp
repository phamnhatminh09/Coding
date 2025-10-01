#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m;
    cin >> n >> m;
    vector<int> a(n), cnt(m, 0);

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        int rem = (a[i] % m + m) % m;
        cnt[rem]++;
    }

    int res = 0;
    
    if (cnt[0] > 0) res += 1;
    
    for (int r = 1; r <= m / 2; ++r) {
        if (r == m - r) {
            if (cnt[r] > 0) res += 1;
        }
        
        else res += max(cnt[r], cnt[m - r]);
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