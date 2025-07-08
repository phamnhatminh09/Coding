#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 3e5 + 5;

void Solve() {
	int n, p, stock[N];
	
	cin >> n >> p;
    for (int i = 0; i < n; i++) cin >> stock[i];
    
    deque<int> sp, mn;
    int curr = 0, maxlen = 1;
    for (int r = 0; r < n; r++) {
        while (!sp.empty() && stock[sp.back()] <= stock[r]) sp.pop_back();
        sp.push_back(r);
        while (!mn.empty() && stock[mn.back()] >= stock[r]) mn.pop_back();
        mn.push_back(r);
        while (stock[sp.front()] - stock[mn.front()] > p) {
            curr++;
            if (!sp.empty() && sp.front() < curr) sp.pop_front();
            if (!mn.empty() && mn.front() < curr) mn.pop_front();
        }
        maxlen = max(maxlen, r - curr + 1);
    }
    cout << maxlen;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}