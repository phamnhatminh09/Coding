#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m;
	cin >> n >> m;
	
	vector<vector<int>> a(n, vector<int>(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) cin >> a[i][j];
	}
	
	vector<vector<int>> prefix(n + 1, vector<int>(m + 1, 0));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= m; ++j) prefix[i][j] = prefix[i][j - 1] + a[i - 1][j - 1];
	}
	
	int sum = INT_MIN;
	
	for (int l = 1; l <= m; ++l) {
		for (int r = l; r <= m; ++r) {
			int curr = 0;
			for (int i = 1; i <= n; ++i) {
				int num = prefix[i][r] - prefix[i][l - 1];
				curr = max(num, curr + num);
				sum = max(sum, curr);
			}
		}
	}
	
	cout << sum;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}