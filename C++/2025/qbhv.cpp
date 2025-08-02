#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	string s;
    cin >> s;
    
    sort(s.begin(), s.end());
    set<string> perm;
    
    do {
        perm.insert(s);
    } while (next_permutation(s.begin(), s.end()));
    
    cout << perm.size() << endl;
    for (const auto& x : perm) cout << x << '\n';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}