#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e6 + 5;
int a[N], b[N];

void Solve() {
	int n, l1, l2;
	cin >> n >> l1 >> l2;
    for (int i = 0; i < n; i++) cin >> a[i];
    
    int res = 0;
    deque<int> dq;
    
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.front() < i-l2) dq.pop_front();
        int j = i - l1;
        if (j >= 0) {
            while (!dq.empty() && b[dq.back()] < b[j]) dq.pop_back();
            dq.push_back(j);
        }
        b[i] = a[i];
        if(!dq.empty()) b[i] += b[dq.front()];
        res = max(res, b[i]);
    }
    cout << res;
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}