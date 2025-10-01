#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n;
	cin >> n;
	
	vector<int> t(n + 1);
	for (int i = 1; i <= n; ++i) cin >> t[i];
	
	vector<int> res(n + 1, -1);
	vector<bool> visited(n + 1, false);
	
	for (int i = 1; i <= n; ++i) {
		if (!visited[i]) {
			stack<int> s;
			int curr = i;
			
			while (true) {
				if (visited[curr]) {
					if (res[curr] == -1) {
						int x = curr;
						vector<int> cycle;
						do {
							cycle.push_back(x);
							x = t[x];
						} while (x != curr);
						for (int y : cycle) res[y] = cycle.size();
					}
					break;
				}
				visited[curr] = true;
				s.push(curr);
				curr = t[curr];
			}
			while (!s.empty()) {
				int y = s.top();
				s.pop();
				if (res[y] == -1) res[y] = res[t[y]] + 1;
			}
		}
	}
	
	for (int i = 1; i <= n; ++i) cout << res[i] << ' ';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}