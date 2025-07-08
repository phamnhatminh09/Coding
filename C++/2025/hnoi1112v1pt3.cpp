#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll n = 1e5 + 5;

struct res {
    int u, x, y;
};

bool cmp(res a, res b) {
    if (a.u == b.u) return a.x < b.x;
    return a.u < b.u;
}

void Solve() {
	int n;
    cin >> n;

    vector<res> ans;

    for (int y = 1; y * y <= n; y++) {
        if (n % y == 0) {
            int x = n / y;
            if (x > y) {
                int u = (x - 1) * (y + 1);
                ans.push_back({u, x, y});
            }
        }
    }

    sort(ans.begin(), ans.end(), cmp);

    cout << ans.size() << "\n";
    for (auto r : ans) cout << r.x << " " << r.y << "\n";
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}