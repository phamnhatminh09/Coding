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
	
	vector<int> h(n);
	vector<long long> j(n);
	for (int i = 0; i < n; ++i) cin >> h[i];
	for (int i = 0; i < n; ++i) cin >> j[i];
	
	vector<int> nxt(n, n);
	stack<int> st;
	for (int i = n - 1; i >= 0; --i) {
		while (!st.empty() && h[st.top()] <= h[i]) st.pop();
		if (!st.empty()) nxt[i] = st.top();
		st.push(i);
	}
	
	int lg = 1;
	long long mx = 0;
	for (long long x : j) mx = max(mx, x);
	while (lg < 63 && (1LL << lg) <= mx) ++lg;
	
	vector<vector<int>> up(lg, vector<int>(n + 1, n));
	for (int i = 0; i < n; ++i) up[0][i] = nxt[i];
	for (int bit = 1; bit < lg; ++bit) {
		for (int i = 0; i < n; ++i) {
			up[bit][i] = up[bit - 1][up[bit - 1][i]];
		}
	}
	
	for (int i = 0; i < n; ++i) {
		int cur = i;
		for (int bit = 0; bit < lg && cur != n; ++bit) {
			if ((j[i] >> bit) & 1LL) cur = up[bit][cur];
		}
		
		if (cur == n) cout << -1 << ' ';
		else cout << h[cur] << ' ';
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