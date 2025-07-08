#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("DEQUY6.INP", "r", stdin);
#define write freopen("DEQUY6.OUT", "w", stdout);
const ll N = 1e5 + 5;

int cntdigit(ll n) {
	int cnt = 0;
	while (n != 0) {
		n /= 10;
		cnt++;
	}
	return cnt;
}

string rev(ll n) {
	string s = "", t = to_string(n);
	for (int i = t.size() - 1; i >= 0; --i) {
		s += t[i];
	}
	return s;
}

/*string recursion(ll n) {
	string s = "", t = to_string(n % 10);
	return s + t + recursion(n % 10);
}*/

void Solve() {
	ll n;
	cin >> n;
	cout << rev(n);
}

int main() {
    faster
    
    Solve();
    
    return 0;
}