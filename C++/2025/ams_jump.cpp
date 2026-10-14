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
	vector<ll> jump(n + 2);
	for (int i = 1; i <= n; ++i) cin >> h[i];
	for (int i = 1; i <= n; ++i) cin >> jump[i];

	stack<int> st;
	for (int i = n; i >= 1; --i) {
		while (!st.empty() && h[st.top()] <= h[i]) st.pop();
		if (!st.empty()) nxt[i] = st.top();
		st.push(i);
	}

	const int lg = 62;
	vector<vector<int>> up(lg, vector<int>(n + 2, n + 1));
	for (int i = 1; i <= n + 1; ++i) up[0][i] = nxt[i];
	for (int bit = 1; bit < lg; ++bit) {
		for (int i = 1; i <= n + 1; ++i) {
			up[bit][i] = up[bit - 1][up[bit - 1][i]];
		}
	}

	for (int i = 1; i <= n; ++i) {
		int cur = i;
		for (int bit = lg - 1; bit >= 0 && cur != n + 1; --bit) {
			if (jump[i] >= (1LL << bit)) {
				jump[i] -= (1LL << bit);
				cur = up[bit][cur];
			}
		}

		if (i > 1) cout << ' ';
		cout << (cur == n + 1 ? -1 : h[cur]);
	}
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}