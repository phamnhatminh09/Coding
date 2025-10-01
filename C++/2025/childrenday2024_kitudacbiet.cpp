#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m, k;
	cin >> n >> m >> k;
	
	string s;
	cin >> s;
	
	unordered_set<char> uset;
	
	for (int i = 0; i < m; ++i) {
		char c;
		cin >> c;
		uset.insert(c);
	}
	
	vector<int> pos;
	for (int i = 0; i < n; ++i) {
		if (uset.count(s[i])) pos.push_back(i);
	}
	
	ll res = 0, l = 0;
	for (int r = 0; r < n; ++r) {
		if (uset.count(s[r])) {
			auto it = lower_bound(pos.begin(), pos.end(), r - k + 1);
			if (it != pos.begin()) {
				--it;
				if (*it >= l) l = *it + 1;
			}
		}
		res += r - l + 1;
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