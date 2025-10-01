#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;
typedef pair<ll, ll> pll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 5e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void Solve() {
	int n;
	cin >> n;
	
	vector<pll> f(n);
	for (int i = 0; i < n; ++i) cin >> f[i].first >> f[i].second;
	
	sort(f.begin(), f.end());
	
	vector<ll> prefix(n + 1, 0);
	for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + f[i].second;
	
	ll res;
	if (n < 1e5) {
	    res = 0;
		for (int i = 0; i < n; ++i) {
			for (int j = i; j < n; ++j) {
				ll ysum = prefix[j + 1] - prefix[i], xdiff = f[j].first - f[i].first, curr = ysum - xdiff;
				res = max(curr, res);
			}
		}
	}
	else {
		res = f[0].second;
		ll ysum = f[0].second;
		int l = 0;
		for (int r = 1; r < n; ++r) {
			ysum += f[r].second;
			
			while (f[r].first - f[l].first > ysum - (f[r].first - f[l].first)) {
				ysum -= f[l].second;
				l++;
			}
			
			res = max(res, ysum - (f[r].first - f[l].first));
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
