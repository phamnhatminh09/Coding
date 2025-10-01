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
		string s;
		cin >> s;
		
		string h = s.substr(0, 2), m = s.substr(3, 2);
		
		if (stoi(h) == 0) cout << 12 << ":" << m << " AM\n";
		else {
			if (stoi(h) > 12) cout << setw(2) << setfill('0') << stoi(h) - 12 << ":" << m << " PM\n";
			else if (stoi(h) == 12) cout << "12:" << m << " PM\n";
			else cout << s << " AM\n";
		}
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}