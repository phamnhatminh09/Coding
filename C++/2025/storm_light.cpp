#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, k, t;
    cin >> n >> k >> t;

    vector<int> v(n + 1, 0);
    for (int i = 0; i < t; ++i) {
        int x;
        cin >> x;
        v[x] = 1;
    }

    int temp = 0;
    for (int i = 1; i <= k; ++i) temp += v[i];

    int res = temp;

    for (int i = k + 1; i <= n; ++i) {
        temp += v[i] - v[i - k];
        res = min(res, temp);
    }

    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}