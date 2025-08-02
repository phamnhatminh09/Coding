#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(const vector<int>& a, int k, double mid) {
    vector<double> psum(a.size() + 1, 0.0);
    for (int i = 0; i < a.size(); ++i) psum[i + 1] = psum[i] + a[i] - mid;

    double min_psum = 0.0;
    for (int i = k; i <= a.size(); ++i) {
        if (psum[i] - min_psum >= 0) return true;
        min_psum = min(min_psum, psum[i - k + 1]);
    }
    
    return false;
}

double cal(const vector<int>& a, int k) {
    double l = *min_element(a.begin(), a.end()), r = *max_element(a.begin(), a.end());
    double x = 1e-6;

    while (r - l > x) {
        double mid = (l + r) / 2;
        if (check(a, k, mid)) l = mid;
        else r = mid;
    }
    
    return l;
}

void Solve() {
	int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    cout << fixed << setprecision(3) << cal(a, k) << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}