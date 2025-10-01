#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, d;
	cin >> n >> d;
	
	vector<int> sumdiv(n + 1, 0);
	for (int i = 1; i <= n; ++i) {
		for (int j = i * 2; j <= n; j += i) sumdiv[j] += i;
	}
	
	int cnt = 0;
	for (int i = 1; i <= n; ++i) {
		if (abs(i - sumdiv[i]) <= d) cnt++;
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