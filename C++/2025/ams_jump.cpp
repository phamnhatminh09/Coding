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


vector<int> prep(int n, const vector<int>& a) {
	vector<int> res(n, -1);
	stack<int> st;
	
	for(int i = n; i >= 0; --i) {
		while (!st.empty() && st.top() <= a[i]) st.pop();
		
		if (!st.empty()) res[i] = st.top();
		st.push(a[i]);
	}
	
	return res;
}

void Solve() {
	int n;
	cin >> n;
	
	vector<int> h(n), j(n);
	for (int i = 0; i < n; ++i) cin >> h[i];
	for (int i = 0; i < n; ++i) cin >> j[i];
	
	h[n] = *max_element(h.begin(), h.end()) + 1;
	vector<int> cnt = prep(n, h);
	
	for (int i = 0; i < n; ++i) {
		if (cnt[i] == h[n]) cnt[i] = n;
		else {
			auto it = find(h.begin(), h.end(), cnt[i]);
			if (it != h.end()) cnt[i] = distance(h.begin(), it);
		}
	}
	
	for (int i = 0; i < n; ++i) {
		int x;
		if (i + j[i] < n) x = cnt[i + j[i] - 1];
		else x = n;
		
		if (h[x] == h[n]) cout << -1 << ' ';
		else {
			if (cnt[i] == cnt[i + 1]) cout << h[x + 1] << ' ';
			else cout << h[x] << ' ';
		}
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