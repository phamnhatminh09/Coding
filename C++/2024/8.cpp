//#include <bits/stdc++.h>
#include <iostream>
#include <iomanip>

using namespace std;
typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
const ll mod = 1e9 + 7;

void Solve () {
	int h, m;
	cin >> h >> m;
	if (h == 1) {
		if (m <= 10) cout << 1 << " " << 01;
		else cout << 2 << " " << 02;
	}
	else if (h == 2) {
		if (m <= 20) cout << 2 << " " << 02;
		else cout << 3 << " " << 03;
	}
	else if (h == 3) {
		if (m <= 30) cout << 3 << " " << 03;
		else cout << 4 << " " << 04;
	}
	else if (h == 4) {
		if (m <= 40) cout << 4 << " " << 04;
		else cout << 5 << " " << 05;
	}
	else if (h == 5) {
		if (m <= 50) cout << 5 << " " << 05;
		else cout << 10 << " " << 01;
	}
	else if (h >= 6 && h < 10) {
		cout << 10 << " " << 01;
	}
	else if (h == 10) {
		if (m <= 0) cout << 10 << " " << 01;
		else cout << 11 << " " << 11;
		
	}
}

int main() {
	faster
	
	Solve();
	
	return 0;
}