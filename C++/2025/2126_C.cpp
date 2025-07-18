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
		
		vector<int> h(n);
		for (int i = 0; i < n; ++i) cin >> h[i];
		
		int maxh = *max_element(h.begin(), h.end());
		
		if (h[k - 1] == maxh) {
			cout << "YES\n";
			continue;
		}
		
		bool check = false;
		for (int i = 0; i < n; ++i) {
			if (h[i] == maxh) {
				if (h[k - 1] > (h[i] - h[k - 1])) {
					check = true;
					break;
				}
			}
		}
		
		cout << (check ? "YES" : "NO") << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}