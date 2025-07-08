#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

ll cal(int n, ll k) {
    ll d = 1, temp = 0, cnt = 0;
    while (true) {
        if (d <= n) cnt = d;
        else cnt = 2 * n - d;
        
        if (temp + cnt >= k) break;
        temp += cnt;
        d++;
    }
    
    ll start = temp + 1, end = start + cnt - 1;
    return (start + end) * cnt / 2;
}


void Solve() {
    int n;
    ll k;
    cin >> n >> k;

    cout << cal(n, k);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}