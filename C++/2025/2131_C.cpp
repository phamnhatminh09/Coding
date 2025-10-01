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

void Solve() {
	int t;
	cin >> t;
	
	while (t--) {
        int n;
        ll k;
        cin >> n >> k;
        vector<ll> S(n), T(n);
        for(int i = 0; i < n; i++) cin >> S[i];
        for(int i = 0; i < n; i++) cin >> T[i];

        vector<ll> ms(n), mt(n);
        
        for(int i = 0; i < n; i++){
            ll a = S[i] % k, c = min(a, k - a);
            ms[i] = c;
        }
        
        for(int i = 0; i < n; i++){
            ll a = T[i] % k, c = min(a, k - a);
            mt[i] = c;
        }
        
        sort(ms.begin(), ms.end());
        sort(mt.begin(), mt.end());
        
        if(ms == mt) cout << "YES\n";
        else cout << "NO\n";
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}