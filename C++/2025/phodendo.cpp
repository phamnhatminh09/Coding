#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int x, n;
    cin >> x >> n;
    
    set<int> pos = {0, x};
    multiset<int> ms = {x};
    
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        
        auto it = pos.upper_bound(p);
        int r = *it, l = *(--it);
        
        ms.erase(ms.find(r - l));
        
        ms.insert(p - l);
        ms.insert(r - p);
        
        pos.insert(p);
        
        cout << *ms.rbegin() << " ";
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}