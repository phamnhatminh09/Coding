#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("CP.INP", "r", stdin);
#define write freopen("CP.OUT", "w", stdout);
const ll N = 1e5 + 5;

vector<bool> sieve(int lim) {
    vector<bool> isp(lim + 1, true);
    isp[0] = isp[1] = false;
    
    for (int p = 2; p * p <= lim; ++p) {
        if (isp[p]) {
            for (int i = p * p; i <= lim; i += p) isp[i] = false;
        }
    }
    
    return isp;
}


void Solve() {
	ll a, b;
    cin >> a >> b;

    int pmax = sqrt(b);
    vector<bool> isp = sieve(pmax);

    int cnt = 0;
    for (int p = 2; p <= pmax; ++p) {
        if (isp[p]) {
            ll square = (ll)p * p;
            if (square >= a && square <= b) cnt++;
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