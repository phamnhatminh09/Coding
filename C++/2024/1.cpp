#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <stdlib.h>
#include <iomanip>

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
//const ll N = 1e5 + 5;

using namespace std;

void Solve() {
	long double x, y;
	cin >> x >> y;
	x = x - 11.0 - (y * 4.4);
	long stage = 0, tax = 0;
	if (x <= 5.0) {
		if (x <= 0.0) stage = 1;
		else {
			stage = 1;
			tax = (long long) ceil(x * 50000);
		}
	}
	else if (5.0 < x && x <= 10.0) {
		stage = 2;
		tax = (long long) ceil((x * 100000) - 250000);
	}
	else if (10.0 < x && x <= 18.0) {
		stage = 3;
		tax = (long long) ceil((x * 150000) - 750000);
	}
	else if (18.0 < x && x <= 32.0) {
		stage = 4;
		tax = (long long) ceil((x * 200000) - 1650000);
	}
	else if (32.0 < x && x <= 52.0) {
		stage = 5;
		tax = (long long) ceil((x * 250000) - 3250000);
	}
	else if (52.0 < x && x <= 80.0) {
		stage = 6;
		tax = (long long) ceil((x * 300000) - 5850000);
	}
	else if (80.0 < x) {
		stage = 7;
		tax = (long long) ceil((x * 350000) - 9850000);
	}
	
	cout << stage << " " << tax;
}

int main() {
    faster

    Solve();

    return 0;
}