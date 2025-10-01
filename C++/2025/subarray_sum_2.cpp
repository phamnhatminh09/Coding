#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, x;
	cin >> n >> x;
	
	vector<int> a(n), psum(n);
	for (int i = 0; i < n; ++i) cin >> a[i];
	
	unordered_map<ll, int> prefix;
	prefix[0] = 1;
	
	ll sum = 0, cnt = 0;
	
	for (int i = 0; i < n; ++i) {
		sum += a[i];
		if (prefix.find(sum - x) != prefix.end()) cnt += prefix[sum - x];
		prefix[sum]++;
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