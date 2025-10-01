#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	ll x;
	string s;
	cin >> s >> x;
	
	ll cnt = 0;
	for (ll i = 0; i < s.size() - 1; ++i) {
		if (s[i] == 'a' && s[i + 1] == 'b') cnt++;
		//cout << cnt << '\n';
	}
	
	cnt *= x;
	if (s[0] == 'b' && s[s.size() - 1] == 'a') cnt += (x - 1);
	
	cout << cnt;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}