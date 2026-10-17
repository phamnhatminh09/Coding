#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const int LOG = 63;

void Solve() {
	int n;
	cin >> n;
	
	vector<int> h(n + 2);
	vector<ll> jumps(n + 1);
	for (int i = 1; i <= n; ++i) cin >> h[i];
	for (int i = 1; i <= n; ++i) cin >> jumps[i];

	vector<int> nxt(n + 2, n + 1);
	stack<int> st;
	for (int i = n; i >= 1; --i) {
		while (!st.empty() && h[st.top()] <= h[i]) st.pop();
		if (!st.empty()) nxt[i] = st.top();
		st.push(i);
	}

	vector<array<int, LOG>> up(n + 2);
	for (int i = 1; i <= n + 1; ++i) up[i].fill(n + 1);
	for (int i = 1; i <= n; ++i) up[i][0] = nxt[i];
	for (int bit = 1; bit < LOG; ++bit) {
		for (int i = 1; i <= n; ++i) {
			up[i][bit] = up[up[i][bit - 1]][bit - 1];
		}
	}

	for (int i = 1; i <= n; ++i) {
		int cur = i;
		for (int bit = LOG - 1; bit >= 0 && cur != n + 1; --bit) {
			if ((jumps[i] >> bit) & 1LL) {
				cur = up[cur][bit];
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