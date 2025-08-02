#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	ll n;
	cin >> n;
	
	ll cnt = 0;
	cnt += n / 5;
	n %= 5;
	
	if (n == 4) cnt += 2;
	else if (n == 3) cnt += 1;
	else if (n == 2) cnt += 1;
	else cnt += 2;
	
	cout << cnt;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}