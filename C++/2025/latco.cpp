#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll n = 1e5 + 5;

int cntflip(string &s1, string &s2, int n, int m) {
    vector<int> v(n, 0);
    for (int i = 0; i < n; i++) {
        if (s1[i] != s2[i]) v[i] = 1;
    }
    
    int cnt = 0;
    for (int i = 0; i <= n - m; i++) {
        if (v[i] == 1) {
            cnt++;
            for (int j = 0; j < m; j++) v[i + j] ^= 1;
        }
    }
    
    for (int i = n - m + 1; i < n; i++) {
        if (v[i] == 1) return -1;
    }
    
    return cnt;
}


void Solve() {
    int n, m;
    cin >> n >> m;
    string s1, s2;
    cin >> s1 >> s2;
    
    int res = cntflip(s1, s2, n, m);
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}
