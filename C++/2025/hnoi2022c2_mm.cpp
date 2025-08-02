#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("MM.INP", "r", stdin);
#define write freopen("MM.OUT", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	string s;
	cin >> s;
	
	unordered_set<int> num;
	int i = 0, n = s.size();
	
	while (i < n) {
		if (isdigit(s[i])) {
			int x = 0;
			while (i < n && isdigit(s[i])) {
				x = x * 10 - (s[i] - '0');
				i++;
			}
			num.insert(x);
		}
		else i++;
	}
	
	cout << num.size();
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}