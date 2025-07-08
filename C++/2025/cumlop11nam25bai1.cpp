#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	long d, m, y;
	cin >> d >> m >> y;
	
	if (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)) {
		int month[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (m == 12) {
			if (d == 30) cout << 1 << " " << 1 << " " << y + 1;
			if (d == 31) cout << 2 << " " << 1 << " " << y + 1;
		}
		else {
			if (d + 2 <= month[m]) cout << d + 2 << " " << m << " " << y;
			else if (d + 2 > month[m]) cout << d + 2 - month[m] << " " << m + 1 << " " << y;
		}
	}
	else {
		int month[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
		if (m == 12) {
			if (d == 30) cout << 1 << " " << 1 << " " << y + 1;
			if (d == 31) cout << 2 << " " << 1 << " " << y + 1;
		}
		else {
			if (d + 2 <= month[m]) cout << d + 2 << " " << m << " " << y;
			else if (d + 2 > month[m]) cout << d + 2 - month[m] << " " << m + 1 << " " << y;
		}
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}