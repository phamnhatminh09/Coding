#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
#define int unsigned long long
const ll N = 1e5 + 5;

string solve(const string &a, const string &b) {
    string c;
    int i = 0, j = 0;
    
    while (i < a.size() && j < b.size()) {
        if (a[i] < b[j]) c += a[i++];
        else if (a[i] > b[j]) c += b[j++];
        else {
            int x = i, y = j;
            while (x < a.size() && y < b.size() && a[x] == b[y]) {
                x++;
                y++;
            }
            
            if (x == a.size() && y == b.size()) c += a[i++];
            else if (x == a.size()) c += b[j++];
            else if (y == b.size()) c += a[i++];
            else if (a[x] < b[y]) c += a[i++];
            else c += b[j++];
        }
    }
    
    while (i < a.size()) c += a[i++];
    
    while (j < b.size()) c += b[j++];
    
    return c;
}

signed main() {
	//read
	//write
    faster
    
    string a, b;
    cin >> a >> b;
    cout << solve(a, b);
    
    return 0;
}