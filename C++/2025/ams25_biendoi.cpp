#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int main() {
	//read
	//write
    faster
    
	long n;
	cin >> n;
	int cnt = 0;
	
	while (n != 1) {
		if (n % 6 == 0) {
			n /= 6;
			cnt++;
		}
		else {
			if (n % 2 == 0) {
				n *= 3;
				cnt++;
			}
			else {
				cout << -1;
				return 0;
			}
		}
	}
	cout << cnt;
    
    return 0;
}