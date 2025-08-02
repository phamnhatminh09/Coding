#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("TG.INP", "r", stdin);
#define write freopen("TG.OUT", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n;
	cin >> n;
	
	while (n--) {
		int t;
		cin >> t;
		
		int end = 480 + t, h = end / 60, m = end % 60;
		
		cout << setw(2) << setfill('0') << h << ':' << setw(2) << setfill('0') << m << '\n';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}