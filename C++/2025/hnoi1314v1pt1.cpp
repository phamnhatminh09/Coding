#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

int maxdiff(const vector<int>& a) {
    int minv = a[0];
    int maxv = INT_MIN;

    for (int j = 1; j < a.size(); j++) {
        maxv = max(maxv, a[j] - minv);
        minv = min(minv, a[j]);
    }
    
    return maxv;
}

void Solve() {
	int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    cout << maxdiff(a);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}