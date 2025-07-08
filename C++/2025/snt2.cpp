#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(int y) {
    if (y <= 1) return false;
    if (y == 2) return true;
    if (y % 2 == 0) return false;
    
    for (int i = 3; i <= sqrt(y); i += 2) {
        if (y % i == 0) return false;
    }
    
    return true;
}

int pr(int y) {
    if (y <= 2) return 2;
    int temp = y;
    
    if (temp % 2 == 0) temp++;
    while (!check(temp)) temp += 2;
    
    return temp;
}

void Solve() {
	int n, x;
    cin >> n >> x;
    
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];
    
    vector<pair<int, int>> v;
    for (int i = 0; i < n; ++i) {
        if (check(a[i])) v.push_back({0, a[i]});
        else {
            int z = pr(a[i]), y = z - a[i];
            v.push_back({y, z});
        }
    }

    vector<int> dp(x + 1, 0);

    for (auto& i : v) {
        int y = i.first, z = i.second;
        for (int j = x; j >= y; --j) {
            if (dp[j - y] + z > dp[j]) dp[j] = dp[j - y] + z;
        }
    }

    cout << dp[x];
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}