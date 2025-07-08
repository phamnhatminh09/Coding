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
const ll N = 1e6 + 5;

using namespace std;

long first (long n, vector<int> &a) {
	for (int i = 2; i < n; i += 2) {
		string ns = to_string(a[i]);
		reverse(ns.begin(), ns.end());
		a[i] = stol(ns);
	}
	long cnt = 0;
	for (int i = 2; i < n; i += 2){
		if (a[i] % 2 == 0) cnt++;
	}
	
	return cnt;
}

void Solve() {
    long n;
    cin >> n;
    vector<int> a(n);
    for (int i = 2; i < n; i += 2) {
    	a[i] = i;
    }
    
    cout << first(n, a);
}

int main() {
    faster

    Solve();

    return 0;
}