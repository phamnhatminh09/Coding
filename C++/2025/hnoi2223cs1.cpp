#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		int t;
		cin >> t;
		int t1 = t / 60, t2 = t % 60;
		//cout << t1 << " " << t2 << endl;
		int h = 8, m = 0;
		h += t1;
		m += t2;
		if (h < 10) {
			if (m < 10) cout << "0" << h << ":" << "0" << m;
			else cout << "0" << h << ":" << m;
		}
		else {
			if (m < 10) cout << h << ":" << "0" << m;
			else cout << h << ":" << m;
		}
		cout << "\n";
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}