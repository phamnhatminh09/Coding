#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int findy(int x) {
	unordered_set<char> digit;
	string s = to_string(x);
	
	for (char c : s) digit.insert(c);
	
	for (int i = 0; i <= 1000; ++i) {
		string y = to_string(i);
		for (char c : y) {
			if (digit.find(c) != digit.end()) return i;
		}
	}
	
	return -1;
}

void Solve() {
	int t;
	cin >> t;
	
	while (t--) {
		int x;
		cin >> x;
		
		cout << findy(x) << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}