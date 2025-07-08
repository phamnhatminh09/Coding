#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

vector<bool> sieve(int limit) {
    vector<bool> isp(limit + 1, true);
    isp[0] = isp[1] = false;
    for (int i = 2; i * i <= limit; ++i) {
        if (isp[i]) {
            for (int j = i * i; j <= limit; j += i) isp[j] = false;
        }
    }
    return isp;
}


void Solve() {
	int n;
	cin >> n;
	
    vector<bool> isp = sieve(2 * n);
    
    long long cnt = 0;
    for (int t = 2; t <= 2 * n; ++t) {
        if (isp[t]) {
            int x_min = max(1, t - n);
            int x_max = min(n, t - 1);
            if (x_min <= x_max) cnt += (x_max - x_min + 1);
        }
    }
    
    cout << cnt;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}