#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

bool check(int d, int k, vector<pair<int, int>>& s) {
    int count = 0;
    for (auto [a, b] : s) {
        count += (b - a) / d;
    }
    return count >= k;
}

int maxlen(int n, int k, vector<pair<int, int>>& s) {
    int l = 1, r = 1e9, res = 1;

    while (l <= r) {
        int m = (l + r) / 2;
        if (check(m, k, s)) {
            res = m;
            l = m + 1;
        }
        else r = m - 1;
    }
    return res;
}

void Solve() {
	int n, k;
    cin >> n >> k;

    vector<pair<int, int>> s(n);
    for (int i = 0; i < n; i++) cin >> s[i].first >> s[i].second;

    cout << maxlen(n, k, s);
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}