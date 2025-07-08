#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int check(const string &n) {
	int len = n.length();
	if (len == 0) return 0;
	
	int last = n.back() - '0';
	if (len == 1) return last % 4;
	int secondlast = n[len - 2] - '0';
	
	return (secondlast * 10 + last % 4);
}

void Solve() {
	int n;
	cin >> n;
	
	vector<string> s(n);
	for (int i = 0; i < n; ++i) cin >> s[i];
	
	int cnt = 0;
	for (int i = 0; i < n - 1; ++i) {
		int num1 = check(s[i]);
		int num2 = check(s[i + 1]);
		if ((num1 + num2) % 4 == 0) cnt++;
	}
	
	cout << cnt;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}