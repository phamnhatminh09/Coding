#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<int> findiv(int n) {
	vector<int> div;
	
	for (int i = 1; i <= sqrt(n); ++i) {
		if (n % i == 0) {
			if (i > 1) div.push_back(i);
			if (i != n / i && n / i > 1) div.push_back(n / i);
		}
	}
	
	sort(div.begin(), div.end());
	return div;
}

void Solve() {
	int n;
	cin >> n;
	
	vector<int> b(n);
	for (int i = 0; i < n; ++i) cin >> b[i];
	
	vector<int> v;
	for (int i = 1; i < n; ++i) v.push_back(abs(b[i] - b[0]));
	
	int x = v[0];
	for (size_t i = 1; i < v.size(); ++i) {
		x = __gcd(x, v[i]);
		if (x == 1) break;
	}
	
	vector<int> div = findiv(x);
	sort(div.begin(), div.end());
	
	for (size_t i = 0; i < div.size(); ++i) {
		if (i != 0) cout << ' ';
		cout << div[i];
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}