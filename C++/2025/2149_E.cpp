#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

static ll cnt(const vector<int>& a, int k, int l, int r){
    if (k <= 0) return 0;
    int n = (int)a.size(), mx = 0;
    
    for (int x : a) mx = max(mx, x);
    
    vector<int> freq(mx + 1, 0);
    int left = 0, diff = 0;
    ll ans = 0;
    
    for (int right = 0; right < n; ++right){
        int v = a[right];
        if (freq[v] == 0) ++diff;
        
        ++freq[v];
        while (diff > k){
            int u = a[left];
            if (--freq[u] == 0) --diff;
            ++left;
        }
        
        int high = right - l + 1;
        if (high >= 0){
            int low = right - r + 1, stlow = max(left, low), sthigh = high;
            if (stlow <= sthigh) ans += (sthigh - stlow + 1);
        }
    }
    
    return ans;
}

void Solve() {
	int t;
    if(!(cin >> t)) return ;
    
    while (t--){
        int n, k, l, r;
        cin >> n >> k >> l >> r;
        vector<ll> a(n);
        for (int i = 0; i < n; ++i) cin >> a[i];

        vector<ll> v = a;
        sort(v.begin(), v.end());
        v.erase(unique(v.begin(), v.end()), v.end());
        vector<int> comp(n);
        for (int i = 0; i < n; ++i) comp[i] = lower_bound(v.begin(), v.end(), a[i]) - v.begin();

        ll ans = cnt(comp, k, l, r) - cnt(comp, k - 1, l, r);
        cout << ans << '\n';
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}