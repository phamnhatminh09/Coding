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
	int q;
	cin >> q;
	
	while (q--) {
		int n;
		string t;
		cin >> n >> t;
		
		string s;
		int i = n - 1;
		while (i >= 0) {
			if (t[i] == '0') {
				string str = t.substr(i - 2, 2);
				int num = stoi(str);
				s += (char) ('a' + num - 1);
				i -= 3;
			}
			else {
				int num = t[i] - '0';
				s += (char) ('a' + num - 1);
				i--;
			}
		}
		
		reverse(s.begin(), s.end());
		cout << s << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}