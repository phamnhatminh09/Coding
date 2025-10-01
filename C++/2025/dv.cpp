#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> ii;
typedef pair<ll, int> li;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);

const ll N = 1e5 + 5;
const ll oo = 1e9;
const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

void Solve() {
	int n;
	cin >> n;
	
	vector<vector<ll>> d(n + 1, vector<ll>(n + 1));
	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) cin >> d[i][j];
	}
	
	vector<int> c(n);
	for (int i = 0; i < n; ++i) cin >> c[i];
	
	reverse(c.begin(), c.end());
	vector<bool> visited(n + 1, false);
	vector<ll> res;
	
	for (int k = 0; k < n; ++k) {
		int v = c[k];
		visited[v] = true;
		
		for (int i = 1; i <= n; ++i) {
			for (int j = 1; j <= n; ++j) {
				if (d[i][j] > d[i][v] + d[v][j]) d[i][j] = d[i][v] + d[v][j];
			}
		}
		
		ll sum = 0;
		for (int i = 1; i <= n; ++i) {
			if (!visited[i]) continue;
			
			for (int j = 1; j <= n; ++j) {
				if (!visited[j] || i == j) continue;
				
				sum += d[i][j];
			}
		}
		
		res.push_back(sum);
	}
	
	reverse(res.begin(), res.end());
	for (auto x : res) cout << x << ' ';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}