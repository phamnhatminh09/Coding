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

void Solve() {
	int t;
	cin >> t;
	
	while (t--) {
		int n;
		cin >> n;
		
		int x, neg = 0, pos = 0, zeros = 0;
		for (int i = 0; i < n; ++i) {
			cin >> x;
			if (x == -1) neg++;
			else if (x == 1) pos++;
			else zeros++;
		}
		
		//cout << neg << ' ' << pos << ' ' << zeros << '\n';
		if (neg % 2 == 0) cout << zeros << '\n';
		else cout << zeros + 2 << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}