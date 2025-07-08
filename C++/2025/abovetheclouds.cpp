#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void solve() {
    int n;
    string s;
    cin >> n >> s;
    
    if (s.find(s[0], 1) != string::npos) {
        cout << "Yes" << endl;
        return;
    }
    
    if (s.rfind(s.back(), n - 2) != string::npos) {
        cout << "Yes" << endl;
        return;
    }
    
    if (n >= 4) {
        string prefix = s.substr(0, 2);
        if (s.find(prefix, 2) != string::npos) {
            cout << "Yes" << endl;
            return;
        }
        string suffix = s.substr(n - 2, 2);
        if (s.rfind(suffix, n - 3) != string::npos) {
            cout << "Yes" << endl;
            return;
        }
    }
    
    cout << "No" << endl;
}

int main() {
	//read
	//write
    faster
    
    int t;
    cin >> t;
    
    while (t--) {
    	solve();
    }
    
    return 0;
}