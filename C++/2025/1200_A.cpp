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
	string s;
	cin >> n >> s;
	
	vector<char> v(10, '0');
	
	for (char c : s) {
		if (c == 'L') {
			for (int i = 0; i < 10; ++i) {
				if (v[i] == '0') {
					v[i] = '1';
					break;
				}
			}
		}
		else if (c == 'R') {
			for (int i = 9; i >= 0; --i) {
				if (v[i] == '0') {
					v[i] = '1';
					break;
				}
			}
		}
		else v[c - '0'] = '0';
	}
	
	for (auto x : v) cout << x;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}