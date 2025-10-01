#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define faster ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
#define read freopen("", "r", stdin);
#define write freopen("", "w", stdout);
const ll N = 1e5 + 5;

struct strc {
    int sum, x, y;
    bool operator>(const strc& other) const {
        return sum > other.sum;
    }
};

vector<int> cal(vector<int>& a, vector<int>& b, int k) {
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    
    priority_queue<strc, vector<strc>, greater<strc>> pq;
    
    for (int i = 0; i < a.size(); ++i) {
        pq.push({a[i] + b[0], i, 0});
    }
    
    vector<int> res;
    while (k-- && !pq.empty()) {
        strc current = pq.top();
        pq.pop();
        res.push_back(current.sum);
        
        if (current.y + 1 < b.size()) {
            pq.push({a[current.x] + b[current.y + 1], current.x, current.y + 1});
        }
    }
    
    return res;
}

void Solve() {
	int m, n, k;
    cin >> m >> n >> k;
    
    vector<int> a(m), b(n);
    for (int i = 0; i < m; ++i) cin >> a[i];
    for (int i = 0; i < n; ++i) cin >> b[i];
    
    vector<int> res = cal(a, b, k);
    
    for (int sum : res) cout << sum << '\n';
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}