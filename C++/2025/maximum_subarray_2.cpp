#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

void Solve() {
	int n, a, b;
	cin >> n >> a >> b;
	
	vector<ll> x(n);
	for (int i = 0; i < n; ++i) cin >> x[i];
	
	vector<ll> prefix(n + 1, 0);
	for (int i = 1; i <= n; ++i) prefix[i] = prefix[i - 1] + x[i - 1];
	
	deque<int> dq;
	ll sum = -LLONG_MAX;
	
	for (int i = a; i <= n; ++i) {
		while (!dq.empty() && dq.front() < i - b) dq.pop_front();
		while (!dq.empty() && prefix[dq.back()] >= prefix[i - a]) dq.pop_back();
		
		dq.push_back(i - a);
		
		if (i >= a) sum = max(sum, prefix[i] - prefix[dq.front()]);
	}
	
	cout << sum;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}