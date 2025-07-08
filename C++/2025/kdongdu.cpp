#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
    int n, k;
    cin >> n >> k;
    
    int a[n+1];
    for(int i = 1; i <= n; i++) cin >> a[i];
    
    vector<vector<int>> v(k);
    for(int i = 1; i <= n; i++) v[i % k].push_back(a[i]);
    
    int res = 0;
    for(int i = 0; i < k; i++) {
        int tmp1 = 0, tmp2 = 0;
        for(int j = 0; j < v[i].size(); j++) {
            if(v[i][j] % 2 == 0) tmp1++;
            else tmp2++;
        }
        res += min(tmp2, tmp1);
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