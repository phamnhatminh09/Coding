#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void gen(int n, int l, int r, string curr, vector<string>& res) {
    if (curr.length() == 2 * n) {
        res.push_back(curr);
        return;
    }
    
    if (l < n) gen(n, l + 1, r, curr + '(', res);
    
    if (r < l) gen(n, l, r + 1, curr + ')', res);
}

void Solve() {
	int n;
    cin >> n;
    
    vector<string> res;
    gen(n, 0, 0, "", res);
    
    sort(res.begin(), res.end());
    for (const string& s : res) cout << s << endl;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}