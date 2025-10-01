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
	int t;
	cin >> t;
	
	while (t--) {
		int n;
        cin >> n;
        
        for (int i = 0; i < n; i++) {
            if (i % 2 == 0) cout << -1;
            else {
                if (i == n - 1) cout << 2;
                else cout << 3;
            }
            if (i < n - 1) cout << " ";
        }
        
        cout << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}