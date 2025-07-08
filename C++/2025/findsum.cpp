#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n;
	cin >> n;
	string s = to_string(n);
	reverse(s.begin(), s.end());
	int rev_n = stoi(s);
	cout << n % 10 + rev_n % 10;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}