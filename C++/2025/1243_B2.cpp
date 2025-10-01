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

void cal() {
	int n;
	string s, t;
	cin >> n >> s >> t;
	
	unordered_map<char, int> m;
	for (int i = 0; i < n; ++i) {
		m[s[i]]++;
		m[t[i]]++;
	}
	
	for (auto [x, v] : m) {
		if (v % 2 != 0) {
			cout << "No\n";
			return;
		}
	}
	
	vector<ii> v;
	for (int i = 0; i < n; ++i) {
		if (s[i] == t[i]) continue;
		
		bool check = false;
		for (int j = i + 1; j < n; ++j) {
			if (s[j] == s[i]) {
				v.emplace_back(j, i);
				swap(s[j], t[i]);
				check = true;
				break;
			}
		}
		
		if (!check) {
			for (int j = i + 1; j < n; ++j) {
				if (t[j] == s[i]) {
					v.emplace_back(i + 1, j);
					swap(s[i + 1], t[j]);
					v.emplace_back(i + 1, i);
					swap(s[i + 1], t[i]);
					check = true;
					break;
				}
			}
		}
		
		if (!check) {
			cout << "No\n";
			return;
		}
	}
	
	cout << "Yes\n" << v.size() << '\n';
	for (auto [u, w] : v) cout << u + 1 << ' ' << w + 1 << '\n';
}

void Solve() {
	int k;
	cin >> k;
	
	while (k--) {
		cal();
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}