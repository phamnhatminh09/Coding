#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll mod = 1e9 + 7;

void Solve() {
	int n, k;
    cin >> n >> k;
    
    vector<int> a(n);
    unordered_set<int> uset;
    for (int i = 0; i < n; ++i) {
        cin >> a[i];
        uset.insert(a[i]);
    }

    sort(a.begin(), a.end());
    vector<bool> visited(n, false);
    int maxx = 0;
    ll res = 1;

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            int curr = a[i];
            vector<int> v;
            
            while (uset.count(curr)) {
                auto it = lower_bound(a.begin(), a.end(), curr);
                int idx = it - a.begin();
                visited[idx] = true;
                v.push_back(curr);
                curr *= 2;
            }

            int l = v.size(), cnt = (l + 1) / 2;
            maxx += cnt;
            
            ll fib[l + 2];
            fib[0] = 1;
            fib[1] = 1;
            
            for (int j = 2; j <= l; ++j) fib[j] = (fib[j - 1] + fib[j - 2]) % mod;
            res = (res * fib[l]) % k;
        }
    }

    cout << maxx << " " << res % k << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}