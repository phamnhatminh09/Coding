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
		int k, x;
		cin >> k >> x;
		
		set<ll> n;
		n.insert(x);
		
		while (k--) {
			set<ll> s;
			
			for (ll i : n) {
				s.insert(2 * i);
				if ((i - 1) % 3 == 0) {
					ll temp = (i - 1) / 3;
					if (temp > 0 && temp % 2 != 0) s.insert(temp);
				}
			}
			
			n = s;
		}
		
		cout << *n.begin() << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}