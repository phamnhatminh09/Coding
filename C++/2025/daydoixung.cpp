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
	
	long a[n];
	for (int i = 0; i < n; ++i) cin >> a[i];
	
	long l = 0, r = n - 1, lsum = a[l], rsum = a[r], cnt = 0;
	while (l <= r) {
		//cout << l << " " << r << " ";
		//cout << lsum << " " << rsum << endl;
		if (lsum < rsum) {
			l++;
			cnt++;
			lsum += a[l];
			//cout << l << " " << lsum << " " << cnt << endl;
		}
		else if (lsum == rsum) {
			lsum = 0;
			rsum = 0;
			l++;
			r--;
			//cout << a[l] << " " << a[r] << endl;
			lsum += a[l];
			rsum += a[r];
		}
		else if (lsum > rsum) {
			r--;
			cnt++;
			rsum += a[r];
			//cout << r << " " << rsum << " " << cnt << endl;
		}
	}
	cout << cnt;
}

signed main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}