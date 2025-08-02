#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("watching.inp", "r", stdin);
#define write freopen("watching.out", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m;
    ll t, k;
    cin >> n >> m >> t >> k;

    vector<ll> a(n), b(m);
    for (int i = 0; i < n; ++i) cin >> a[i];
    for (int i = 0; i < m; ++i) cin >> b[i];

    ll curr = 0, atime = 0, btime = 0;
    bool check = true;

    while (curr < t) {
        if (check) {
            auto it = upper_bound(a.begin(), a.end(), curr);
            ll ad = (it != a.end()) ? *it : t + k, end = min(ad, t);

            atime += end - curr;
            curr = end;

            if (curr < t && ad <= curr) {
                auto it = upper_bound(b.begin(), b.end(), curr);
                if (it != b.begin()) {
                    --it;
                    if (*it <= curr && curr < *it + k) continue;
                }
                
                check = false;
            }
        }
        else {
            auto it = upper_bound(b.begin(), b.end(), curr);
            ll ad = (it != b.end()) ? *it : t + k, end = min(ad, t);

            btime += end - curr;
            curr = end;

            if (curr < t && ad <= curr) {
                auto it = upper_bound(a.begin(), a.end(), curr);
                if (it != a.begin()) {
                    --it;
                    if (*it <= curr && curr < *it + k) continue;
                }
                check = true;
            }
        }
    }

    cout << atime << " " << btime;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}