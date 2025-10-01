#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 3e3 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};
const int mod = 1e9 + 7;

int n, k, a[N];
ll dp[N];

int cnt(const vector<int>& v) {
	int inv = 0;
	
	for (int i = 0; i < v.size(); ++i) {
		for (int j = i + 1; j < v.size(); ++j) {
			if (v[i] > v[j]) inv++;
		}
	}
	
	return inv;
}

void Solve() {
	cin >> n >> k;
	
	for (int i = 1; i <= n; ++i) cin >> a[i];
	
	dp[0] = 1;
	for (int i = 1; i <= n; ++i) {
		vector<int> v;
		ll sum = 0;
		
		for (int j = i; j >= 1; --j) {
			v.insert(v.begin(), a[j]);
			int inv = cnt(v);
			
			if (inv > k) break;
			
			sum = (sum + dp[j - 1]) % mod;
		}
		
		dp[i] = sum;
	}
	
	cout << dp[n];
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}