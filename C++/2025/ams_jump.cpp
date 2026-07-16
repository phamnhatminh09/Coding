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
	int n;
	if (!(cin >> n)) return;

	vector<int> h(n + 2), jumps(n + 2), nxt(n + 2, n + 1);
	for (int i = 1; i <= n; ++i) cin >> h[i];
	for (int i = 1; i <= n; ++i) cin >> jumps[i];

	stack<int> st;
	for (int i = n; i >= 1; --i) {
		while (!st.empty() && h[st.top()] <= h[i]) st.pop();
		nxt[i] = st.empty() ? n + 1 : st.top();
		st.push(i);
	}

	int lg = 1;
	while ((1 << lg) <= n + 1) ++lg;
	vector<vector<int>> up(lg, vector<int>(n + 2, n + 1));
	for (int i = 1; i <= n; ++i) up[0][i] = nxt[i];

	for (int level = 1; level < lg; ++level) {
		for (int i = 1; i <= n; ++i) {
			up[level][i] = up[level - 1][up[level - 1][i]];
		}
	}

	for (int i = 1; i <= n; ++i) {
		int cur = i;
		int steps = jumps[i];
		for (int level = lg - 1; level >= 0; --level) {
			if (steps >= (1 << level)) {
				steps -= (1 << level);
				cur = up[level][cur];
				if (cur == n + 1) break;
			}
		}

		cout << (cur == n + 1 ? -1 : h[cur]) << ' ';
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}


/*
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
const int lg = 20;

int n, h[N], J[N], nxt[N], up[N][lg];

void Solve() {
	cin >> n;
    for (int i = 1; i <= n; i++) cin >> h[i];
    for (int i = 1; i <= n; i++) cin >> J[i];

    stack<int> st;
    for (int i = n; i >= 1; i--) {
        while (!st.empty() && h[st.top()] <= h[i]) st.pop();
        
        if (st.empty()) nxt[i] = n + 1;
        else nxt[i] = st.top();
        
        st.push(i);
    }
    
    for (int i = 1; i <= n; i++) up[i][0] = nxt[i];
    
    for (int j = 1; j < lg; j++) {
        for (int i = 1; i <= n; i++) {
            if (up[i][j - 1] == n + 1) up[i][j] = n+1;
            else up[i][j] = up[up[i][j - 1]][j - 1];
        }
    }
    
    for (int i = 1; i <= n; i++) {
        int cur = i, steps = J[i];
        
        for (int j = lg - 1; j >= 0; j--) {
            if (steps >= (1 << j)) {
                steps -= (1 << j);
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
*/