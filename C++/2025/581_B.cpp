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

void Solve() {
	int n;
	cin >> n;
	
	vector<int> h(n);
	for (int i = 0; i < n; ++i) cin >> h[i];
	
	vector<int> maxx(n, 0);
	int curr = 0;
	for (int i = n - 1; i >= 0; --i) {
		maxx[i] = curr;
		curr = max(h[i], curr);
	}
	
	vector<int> res(n);
	for (int i = 0; i < n; ++i) {
		if (maxx[i] == 0) res[i] = 0;
		else res[i] = max(0, maxx[i] + 1 - h[i]);
	}
	
	for (auto x : res) cout << x << ' ';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}