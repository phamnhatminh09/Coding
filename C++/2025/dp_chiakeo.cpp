#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(int num) {
    if (num <= 1) return false;
    if (num == 2) return true;
    if (num % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(num); i += 2) {
        if (num % i == 0) return false;
    }
    
    return true;
}

void Solve() {
	int n, q;
    cin >> n >> q;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    
    vector<long long> v1(n + 2, 0), v2(n + 2, 0);
    
    while (q--) {
        int t, l, r, val;
        cin >> t >> l >> r >> val;
        if (t == 1) {
            v1[l] += val;
            v1[r + 1] -= val;
        }
        else {
            v2[l] += val;
            v2[r + 1] -= val;
        }
    }
    
    vector<long long> pcandy(n + 1, 0), ccandy(n + 1, 0);
    for (int i = 1; i <= n; ++i) {
        pcandy[i] = pcandy[i - 1] + v1[i];
        ccandy[i] = ccandy[i - 1] + v2[i];
    }
    
    for (int i = 1; i <= n; ++i) {
        if (check(a[i])) cout << pcandy[i] << " ";
        else cout << ccandy[i] << " ";
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}