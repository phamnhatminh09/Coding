#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, q;
	cin >> n >> q;
	string s;
	cin >> s;
	
	vector<int> prefix(n + 1, 0);
	for (int i = 0; i < n; ++i) {
		int c = s[i] - 'a';
		prefix[i + 1] = prefix[i] ^ (1 << c);
	}
	
	while (q--) {
		int l, r;
		cin >> l >> r;
		int x = prefix[r + 1] ^ prefix[l], cnt = __builtin_popcount(x);
		cout << cnt / 2 << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}