#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

string find(const string &s) {
    int n = s.size();
    vector<int> lps(n, 0);
    int len = 0, i = 1;
    
    while (i < n) {
        if (s[i] == s[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) len = lps[len - 1];
         	else {
                lps[i] = 0;
                i++;
            }
        }
    }
    
    int x = n - lps[n - 1];
    if (n % x == 0) return s.substr(0, x);
    else return s;
}


void Solve() {
	string s, t;
    getline(cin, s);
    getline(cin, t);
    
    if (find(s) == find(t)) cout << find(s);
    else cout << "NO";
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}