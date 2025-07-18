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
		
		vector<int> a(n);
		for (int i = 0; i < n; ++i) cin >> a[i];
		
		int res = 0, curr = 0;
		for (int i = 0; i < n; ++i) {
			if (a[i] == 0) {
				curr++;
				if (curr >= k) {
					res++;
					curr = 0;
					i++;
				}
			}
			else curr = 0;
		}
		
		cout << res << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}