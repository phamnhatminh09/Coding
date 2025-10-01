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

void Solve() {
	int n;
	cin >> n;
	
	vector<ll> a(n + 1), prefix(n + 1, 0), suffix(n + 2, 0);;
	for (int i = 0; i < n; ++i) cin >> a[i];
	
	for (int i = 1; i <= n; ++i) prefix[i] = prefix[i - 1] + a[i - 1];
	
	for (int i = n; i >= 1; --i) suffix[i] = suffix[i + 1] + a[i - 1];
	
	ll res = LLONG_MAX;
	
	for (int p = 1; p < n; ++p) {
		ll diff = abs(prefix[p] - suffix[p + 1]);
		
		if (diff < res) res = diff;
		if (diff == 0) break;
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

/*
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

void Solve() {
    int n;
    if(!(cin >> n)) return;
    
    vector<ll>a(n);
    ll sum = 0;
    
    for(int i = 0; i < n; i++) {
    	cin >> a[i];
    	sum += a[i];
    }

    ll pref = 0, ans = LLONG_MAX;
    for(int i = 0; i < n - 1; i++){
        pref += a[i];
        ans = min(ans, llabs(sum - 2 * pref));
    }
    
    cout << ans;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}
*/