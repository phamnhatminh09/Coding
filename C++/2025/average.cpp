#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(const vector<int>& a, int k, double m) {
    int n = a.size();
    vector<double> prefix(n + 1, 0.0);
    for (int i = 0; i < n; ++i) prefix[i + 1] = prefix[i] + a[i] - m;

    double x = 0.0;
    for (int i = k; i <= n; ++i) {
        if (prefix[i] - x >= 0) return true;
        if (i - k + 1 >= 0) x = min(x, prefix[i - k + 1]);
    }
    return false;
}

void Solve() {
	int n, k, h;
    cin >> n >> k >> h;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
    }

    double l = *min_element(a.begin(), a.end()), r = *max_element(a.begin(), a.end()), ans = l;

    for (int i = 0; i < 100; ++i) {
        double m = (l + r) / 2;
        if (check(a, k, m)) {
            ans = m;
            l = m;
        }
        else r = m;
    }

    if (h == 0) cout << (int)floor(ans);
    else cout << fixed << setprecision(3) << ans;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}