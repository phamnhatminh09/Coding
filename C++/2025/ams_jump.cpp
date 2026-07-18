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

const int lg = 62;

void Solve() {
	int n;
	cin >> n;
	
	vector<int> h(n + 2), nxt(n + 2, n + 1);
	vector<ll> jump(n + 2);
	vector<array<int, lg>> up(n + 2);
	
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) cin >> jump[i];

    stack<int> st;
    for (int i = n; i >= 1; i--) {
        while (!st.empty() && h[st.top()] <= h[i]) st.pop();
        
        if (st.empty()) nxt[i] = n + 1;
        else nxt[i] = st.top();
        
        st.push(i);
    }
    
    for (int i = 1; i <= n + 1; i++) up[i].fill(n + 1);
    for (int i = 1; i <= n; i++) up[i][0] = nxt[i];
    
    for (int j = 1; j < lg; j++) {
        for (int i = 1; i <= n; i++) {
            if (up[i][j - 1] == n + 1) up[i][j] = n+1;
            else up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        int cur = i;
        ll steps = jump[i];
        
        for (int j = lg - 1; j >= 0; j--) {
            if (steps >= (1LL << j)) {
                steps -= (1LL << j);
                cur = up[cur][j];
                
                if (cur == n + 1) break;
            }
        }
        
        if (cur == n + 1) cout << -1 << " ";
        else cout << h[cur] << " ";
    }
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}