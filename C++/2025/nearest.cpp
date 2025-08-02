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
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; ++i) cin >> a[i];

    vector<int> res(n + 1, 0);
    stack<int> st;

    for (int i = 1; i <= n; ++i) {
        while (!st.empty() && a[st.top()] >= a[i]) st.pop();
        
        if (!st.empty()) res[i] = st.top();
        else res[i] = 0;
        
        st.push(i);
    }

    for (int i = 1; i <= n; ++i) cout << res[i] << " ";
}

int main() {
	//read
	//write
    faster
    
    Solve();
    
    return 0;
}