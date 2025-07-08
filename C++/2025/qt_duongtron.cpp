#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
#define endl '\n'
const ll N = 1e5 + 5;

void Solve() {
	int q;
	cin >> q;
	
	while(q--) {
		long x1, y1, r1, x2, y2, r2;
		cin >> x1 >> y1 >> r1 >> x2 >> y2 >> r2;
		
		ll dx = x1 - x2, dy = y1 - y2;
		ll oo = dx * dx + dy * dy;
		ll Rr = r1 + r2;
		ll rR = llabs(r1 - r2);
		ll Rr2 = Rr * Rr;
		ll rR2 = rR * rR;
		
		if (oo < Rr2 && oo > rR2) cout << 2 << endl;
		else if (oo == Rr2 || oo == rR2) {
			if (oo == 0) cout << 0 << endl;
			else cout << 1 << endl;
		}
		else if (oo > Rr2 || oo < rR2) cout << 0 << endl;
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}