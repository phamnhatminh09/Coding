#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll cnt0(ll m) {
    ll cnt = 0;
    
    while (m > 0) {
        m /= 5;
        cnt += m;
    }
    
    return cnt;
}

ll mfind(ll n) {
    ll l = 0, r = 5 * n, res = r;
    
    while (l <= r) {
        ll mid = l + (r - l) / 2, zero = cnt0(mid);
        
        if (zero >= n) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    
    return res;
}

void Solve() {
	int t;
    cin >> t;
    
    while (t--) {
    	ll q;
    	cin >> q;
    	
    	cout << mfind(q) << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}