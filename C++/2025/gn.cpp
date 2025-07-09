#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 2e6 + 5;
int pref[26][N];

void Solve() {
	string s, t;
    cin >> s >> t;

    int m = s.size(), n = t.size();
    
    for (int i = 0; i < n; ++i) {
        int ch = t[i] - 'a';
        for (int c = 0; c < 26; ++c) pref[c][i + 1] = pref[c][i] + (c == ch);
    }
    
    long long res = 0;
    for (int i = 0; i < m; ++i) {
        int ch = s[i] - 'a', l = i, r = n - m + i;
        if (l <= r) res += pref[ch][r + 1] - pref[ch][l];
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