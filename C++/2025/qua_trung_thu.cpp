#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    vector<long long> sum(n - k + 1);
    long long temp = 0;
    for (int i = 0; i < k; ++i) temp += a[i];
    
    sum[0] = temp;
    for (int i = 1; i <= n - k; ++i) {
        temp += a[i + k - 1] - a[i - 1];
        sum[i] = temp;
    }

    vector<long long> left(n - k + 1);
    left[0] = sum[0];
    for (int i = 1; i < n - k + 1; ++i) left[i] = max(left[i - 1], sum[i]);

    vector<long long> right(n - k + 1);
    right[n - k] = sum[n - k];
    for (int i = n - k - 1; i >= 0; --i) right[i] = max(right[i + 1], sum[i]);

    long long res = 0;
    for (int i = 0; i < n - 2 * k + 1; ++i) res = max(res, sum[i] + right[i + k]);

    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}