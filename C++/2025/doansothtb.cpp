#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

vector<ll> pr;

void sieve() {
    const int MN = 1e4;
    vector<bool> isp(MN + 1, true);
    isp[0] = isp[1] = false;
    for (int i = 2; i * i <= MN; ++i) {
        if (isp[i]) {
            for (int j = i * i; j <= MN; j += i) isp[j] = false;
        }
    }
    
    for (int i = 2; i <= MN; ++i) {
        if (isp[i]) pr.push_back(i);
    }
}

ll check(ll y) {
    cout << "ucln " << y << endl;
    cout.flush();
    ll res;
    cin >> res;
    return res;
}

void Solve() {
	ll ans = 1;
	
	for (ll prime : pr) {
		ll p = prime;
		while (true) {
			ll gcd = check(p);
			if (gcd % p != 0) break;
			p *= prime;
		}
		
		p /= prime;
		if (p >= prime) ans *= p;
	}
	
	cout << "traloi " << ans;
}

int main() {
	//read
	//write
    faster

    sieve();
    
    Solve();
    
    return 0;
}