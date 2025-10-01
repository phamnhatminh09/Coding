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
	int k;
	cin >> k;
	
	while (k--) {
		int n;
		string s, t;
		cin >> n >> s >> t;
		
		vector<int> v;
		for (int i = 0; i < n; ++i) {
			if (s[i] != t[i]) v.push_back(i);
		}
		
		if (v.size() != 2) {
			cout << "No\n";
			continue;
		}
		
		if (s[v[0]] == s[v[1]] && t[v[1]] == t[v[0]]) cout << "Yes\n";
		else cout << "No\n";
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}