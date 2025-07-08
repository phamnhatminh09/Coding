//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include <stack>

using namespace std;

//typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
//const ll N = 1e6 + 5;

void Solve() {
	int d, m, y, k;
	cin >> d >> m >> y >> k;
	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8 || m == 10 || m == 12) cout << 31;
	else if (m != 2) cout << "30";
	else if (m == 2) {
		if (y % 100 == 0) {
			if (y % 400 == 0) cout << "Leap";
			else cout << "Normal";
		}
		else if (y % 100 != 0) {
			if (y % 4 == 0) cout << "Leap";
			else cout << "Normal";
		}
	}
	
	k = k % 7;
	long d1 = d % 7;
	
}

int main() {
    faster
    
    Solve();

    return 0;
}