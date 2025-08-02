#include <bits/stdc++.h>

using namespace std;

typedef ll ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("BS.INP", "r", stdin);
#define write freopen("BS.OUT", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	ll n, x;
    cin >> n >> x;

    int cnt = 0;
    for (ll i = 1; i <= min((ll)sqrt(x), n); ++i) {
        if (x % i == 0) {
            ll j = x / i;
            if (j <= n) {
                if (i == j) cnt += 1;
                else cnt += 2;
            }
        }
    }

    cout << cnt;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}