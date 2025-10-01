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

void Solve() {
	int k;
	cin >> k;
	
	vector<int> d(k, 1e9);
	priority_queue<ii, vector<ii>, greater<ii>> pq;
	
	for (int i = 1; i <= 9; ++i) {
		int m = i % k;
		if (i < d[m]) {
			d[m] = i;
			pq.push({i, m});
		}
	}
	
	while (!pq.empty()) {
		int du = pq.top().first, u = pq.top().second;
		pq.pop();
		
		if (u == 0) {
			cout << du;
			break;
		}
		
		if (du > d[u]) continue;
		
		for (int w = 0; w <= 9; ++w) {
			int v = (u * 10 + w) % k;
			
			if (d[v] > du + w) {
				d[v] = du + w;
				pq.push({du + w, v});
			}
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