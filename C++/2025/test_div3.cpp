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
    vector<ll> a(n);
    vector<ll> psum(n + 1, 0);
    ll sum = 0;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        sum += a[i];
        psum[i + 1] = psum[i] + a[i];
    }

    ll x = sum / 3, y = 2 * x, j = 0, k = 0;
    ll res = LLONG_MAX, ai = 0, aj = 0, ak = 0;

    for (int i = 0; i < n; ++i) {
        while (j <= i || (j < i + n && psum[j % n + 1] - psum[i] < x)) ++j;
        while (k <= j || (k < i + n && psum[k % n + 1] - psum[i] < y)) ++k;

        for (int dj = -1; dj <= 1; ++dj) {
            for (int dk = -1; dk <= 1; ++dk) {
                int y = (j + dj) % n, z = (k + dk) % n;
                
                if (y < 0) y += n;
                if (z < 0) z += n;
                
                if (i < y && y < z) {
                    ll sum1 = psum[y] - psum[i], sum2 = psum[z] - psum[y], sum3 = sum - sum1 - sum2;
                    ll curr = max({sum1, sum2, sum3}) - min({sum1, sum2, sum3});
                    
                    if (curr < res) {
                        res = curr;
                        ai = i;
                        aj = y;
                        ak = z;
                    }
                }
            }
        }
    }

    cout << res << '\n' << ai + 1 << ' ' << aj + 1 << ' ' << ak + 1;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}