#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
    long x, n, k, cnt = 0;
    map <long, long> m;
    
    cin >> n >> x;
    for (int i = 1; i <= n; ++i) {
        cin >> k;
        cnt += m[x - k];
        m[k]++;
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