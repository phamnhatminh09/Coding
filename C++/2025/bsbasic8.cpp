#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(const vector<long long>& psum, int n, int L) {
    long long minn = 0;
    
    for (int i = L; i <= n; ++i) {
        if (psum[i] - minn >= 0) return true;
        minn = min(minn, psum[i - L + 1]);
    }
    
    return false;
}

int cal(const vector<int>& a) {
    int n = a.size();
    
    vector<long long> psum(n + 1, 0);
    for (int i = 0; i < n; ++i) psum[i + 1] = psum[i] + a[i];

    int l = 1, r = n, res = -1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        
        if (check(psum, n, m)) {
            res = m;
            l = m + 1;
        }
        else r = m - 1;
    }
    
    return res;
}

void Solve() {
	int n;
    cin >> n;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    cout << cal(a);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}