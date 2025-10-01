#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5;
const ll oo = 1e18;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void Solve() {
	int n, k;
    cin >> n >> k;
    
    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<bool> v(n, false);

    for (int x = 1; x < (1 << n); ++x) {
        int sum = 0;
        vector<int> team;
        
        for (int i = 0; i < n; ++i) {
            if (x & (1 << i)) {
                sum += p[i];
                team.push_back(i);
            }
        }
        
        if (sum >= k) {
            for (int i : team) {
                bool check = false;
                
                for (int y = x ^ (1 << i); y > 0; y = (y - 1) & (x ^ (1 << i))) {
                    int curr = 0;
                    
                    for (int j = 0; j < n; ++j) {
                        if (y & (1 << j)) curr += p[j];
                    }
                    
                    if (curr >= k) {
                        check = true;
                        break;
                    }
                }
                
                if (!check) v[i] = true;
            }
        }
    }

    for (bool b : v) cout << (b ? '1' : '0');
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}