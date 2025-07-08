#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	long n;
	cin >> n;
	
	long sum = (n / 9) * ((n / 9) + 1) / 2;
	cout << 9 * sum;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}