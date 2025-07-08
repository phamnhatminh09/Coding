#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll mod = 1e9 + 7;

unordered_map<int, int> pf(int x) {
    unordered_map<int, int> fact;
    for (int i = 2; i * i <= x; ++i) {
        while (x % i == 0) {
            fact[i]++;
            x /= i;
        }
    }
    
    if (x > 1) fact[x]++;
    return fact;
}

void Solve() {
	int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    unordered_map<int, int> mp;
    for (int num : a) {
        if (num == 1) continue;
        auto fact = pf(num);
        for (auto& [p, cnt] : fact) {
            if (mp[p] < cnt) mp[p] = cnt;
        }
    }

    long long res = 1;
    for (auto& [p, cnt] : mp) {
        int temp = (cnt % 2 == 0) ? cnt : cnt + 1;
        for (int i = 0; i < temp; ++i) res = (res * p) % mod;
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
