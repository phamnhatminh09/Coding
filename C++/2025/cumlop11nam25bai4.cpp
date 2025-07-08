#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, m;
    cin >> n >> m;
    vector<int> a(n);
    unordered_map<int, long long> cnt;

    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        int r = a[i] % m;
        cnt[r]++;
    }

    long long res = 0;
    for (auto& [r, count] : cnt) res += count * (count - 1);

    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}