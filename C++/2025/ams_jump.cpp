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
	cin >> n;
	
	vector<int> h(n + 2), nxt(n + 2, n + 1);
	vector<long long> j(n + 1);
	for (int i = 1; i <= n; ++i) cin >> h[i];
	for (int i = 1; i <= n; ++i) cin >> j[i];

	stack<int> st;
	for (int i = n; i >= 1; --i) {
		while (!st.empty() && h[st.top()] <= h[i]) st.pop();
		nxt[i] = st.empty() ? n + 1 : st.top();
		st.push(i);
	}

	long long maxJump = *max_element(j.begin() + 1, j.end());
	int lg = 1;
	while ((1LL << lg) <= max(maxJump, static_cast<long long>(n + 1))) ++lg;

	vector<vector<int>> up(lg, vector<int>(n + 2, n + 1));
	for (int i = 1; i <= n; ++i) up[0][i] = nxt[i];
	for (int k = 1; k < lg; ++k) {
		for (int i = 1; i <= n + 1; ++i) {
			up[k][i] = up[k - 1][up[k - 1][i]];
		}
	}

	for (int i = 1; i <= n; ++i) {
		int cur = i;
		long long steps = j[i];
		for (int k = lg - 1; k >= 0 && cur != n + 1; --k) {
			if (steps >= (1LL << k)) {
				steps -= (1LL << k);
				cur = up[k][cur];
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