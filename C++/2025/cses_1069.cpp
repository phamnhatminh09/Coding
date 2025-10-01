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
	string s;
	cin >> s;
	
	int res = 1, cnt = 1;
	for (int i = 1; i < s.size(); ++i) {
		if (s[i] == s[i - 1]) cnt++;
		else cnt = 1;
		res = max(res, cnt);
	}
	
	cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}