#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int t;
	cin >> t;
	
	while (t--) {
		int n, k;
		cin >> n >> k;
		
		vector<vector<int>> casino(n, vector<int>(3));
		for (int i = 0; i < n; ++i) cin >> casino[i][0] >> casino[i][1] >> casino[i][2];
		
		sort(casino.begin(), casino.end(), [](const vector<int>& a, const vector<int>& b) {
			if (a[0] != b[0]) return a[0] < b[0];
			return a[1] < b[1];
		});
		
		bool check;
		
		do {
			check = false;
			for (int i = 0; i < n; ++i) {
				if (casino[i][0] <= k && k <= casino[i][1]) {
					if (casino[i][2] > k) {
						k = casino[i][2];
						check = true;
					}
				}
			}
		} while(check);
		
		cout << k << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}