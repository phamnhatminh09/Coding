#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
#define int long long

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int32_t main() {
	//read
	//write
	faster

    int n, k;
    cin >> n >> k;

    vector<int> a(n + 1), b(k + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= k; ++i) cin >> b[i];
    
    bool check = true;
    for (int i = 1; i <= k; ++i) {
        if (b[i] != 1) {
            check = false;
            break;
        }
    }

    if (check) {
        int sum = 0;
        for (int i = 1; i <= k; ++i) sum += a[i];
        
        int res = sum;
        for (int i = k + 1; i <= n; ++i) {
            sum += a[i] - a[i - k];
            res = max(res, sum);
        }
        
        cout << res << '\n';
        return 0;
    }
    
    bool is_linear = true;
    for (int i = 1; i <= k; ++i) {
        if (b[i] != i) {
            is_linear = false;
            break;
        }
    }

    if (is_linear) {
        vector<int> v(n + 1), psum(n + 1);
        for (int i = 1; i <= n; ++i) {
            v[i] = v[i - 1] + a[i];
            psum[i] = psum[i - 1] + a[i] * i;
        }

        int res = LLONG_MIN;
        for (int i = 1; i <= n - k + 1; ++i) {
            int j = i + k - 1, sum = psum[j] - psum[i - 1] - (i - 1) * (v[j] - v[i - 1]);
            res = max(res, sum);
        }
        
        cout << res << '\n';
        return 0;
    }
    
    int res = LLONG_MIN;
    for (int i = 1; i <= n - k + 1; ++i) {
        int sum = 0;
        for (int j = 0; j < k; ++j) sum += a[i + j] * b[j + 1];
        
        res = max(res, sum);
    }
    
    cout << res;
}